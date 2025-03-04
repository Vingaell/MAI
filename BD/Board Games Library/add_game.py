import streamlit as st
from database import get_connection

# Функция для получения следующего game_id
def get_next_game_id():
    try:
        with get_connection() as conn:
            with conn.cursor() as cur:
                cur.execute("SELECT COALESCE(MAX(game_id), 0) + 1 FROM games")
                next_game_id = cur.fetchone()[0]
                return next_game_id
    except Exception as e:
        st.error(f"Ошибка при генерации game_id: {e}")
        return None

# Функция для получения существующих тегов
def get_existing_tags():
    try:
        with get_connection() as conn:
            with conn.cursor() as cur:
                cur.execute("SELECT tag_id, name FROM tags")
                tags = cur.fetchall()
                return tags
    except Exception as e:
        st.error(f"Ошибка при получении тегов: {e}")
        return []

# Функция для добавления новой игры в базу данных
def add_new_game(game_id, game_name, min_players, max_players, release_year, play_time, age_rating, selected_tags):
    try:
        with get_connection() as conn:
            with conn.cursor() as cur:
                # Вставка новой игры в таблицу games
                cur.execute("""
                    INSERT INTO games (game_id, game_name, min_players, max_players, release_year, play_time, age_rating)
                    VALUES (%s, %s, %s, %s, %s, %s, %s)
                """, (game_id, game_name, min_players, max_players, release_year, play_time, age_rating))

                # Получаем максимальное значение id в таблице games_to_tags
                cur.execute("SELECT COALESCE(MAX(id), 0) FROM games_to_tags")
                max_id = cur.fetchone()[0]

                # Добавление тегов в таблицу games_to_tags (связующая таблица)
                for i, tag_id in enumerate(selected_tags, start=max_id + 1):
                    cur.execute("""
                        INSERT INTO games_to_tags (id, game_id, tag_id)
                        VALUES (%s, %s, %s)
                    """, (i, game_id, tag_id))

                conn.commit()
    except Exception as e:
        st.error(f"Ошибка при добавлении игры в базу данных: {e}")


# Основная функция для отображения интерфейса добавления игры
def display_add_game_form():
    st.subheader("Добавить новую игру")

    # Генерация нового game_id
    game_id = get_next_game_id()

    if game_id is None:
        st.error("Не удалось получить следующий game_id.")
        return

    # Форма для ввода данных игры
    with st.form(key="add_game_form"):
        game_name = st.text_input("Название игры")
        min_players = st.number_input("Минимальное количество игроков", min_value=1)
        max_players = st.number_input("Максимальное количество игроков", min_value=1)
        release_year = st.number_input("Год выпуска", min_value=1900, max_value=2100)
        play_time = st.number_input("Время игры (в минутах)", min_value=1)
        age_rating = st.number_input("Возрастной рейтинг", min_value=0, max_value=18)

        # Выбор тегов для игры
        tags = get_existing_tags()
        tag_options = {tag[1]: tag[0] for tag in tags}  # Создаем словарь tag_name -> tag_id
        selected_tags = st.multiselect("Выберите теги", list(tag_options.keys()))

        submit_button = st.form_submit_button("Добавить игру")

        # Проверяем, был ли нажат submit и все ли данные введены корректно
        if submit_button:
            if not game_name or not min_players or not max_players or not release_year or not play_time or not age_rating or not selected_tags:
                st.warning("Пожалуйста, заполните все поля и выберите хотя бы один тег.")
            else:
                try:
                    # Добавление новой игры в базу данных
                    add_new_game(game_id, game_name, min_players, max_players, release_year, play_time, age_rating, [tag_options[tag] for tag in selected_tags])
                    st.success(f"Игра '{game_name}' успешно добавлена в базу данных!")
                except Exception as e:
                    st.error(f"Произошла ошибка при добавлении игры: {e}")

