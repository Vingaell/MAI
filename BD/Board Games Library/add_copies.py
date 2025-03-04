import streamlit as st
from database import get_connection

def get_next_copy_id():
    """
    Генерация следующего copy_id на основе уже существующих.
    """
    try:
        with get_connection() as conn:
            with conn.cursor() as cur:
                cur.execute("SELECT COALESCE(MAX(copy_id), 0) FROM copies")
                max_id = cur.fetchone()[0]
                return max_id
    except Exception as e:
        st.error(f"Ошибка при генерации copy_id: {e}")
        return None

def add_game_copies():
    st.subheader("Добавление копий игры")

    try:
        # Получение списка игр
        with get_connection() as conn:
            with conn.cursor() as cur:
                cur.execute("SELECT game_id, game_name FROM games ORDER BY game_name")
                games = cur.fetchall()

                cur.execute("SELECT location_id, location_name, location_address FROM locations ORDER BY location_name")
                locations = cur.fetchall()

        if games and locations:
            # Выбор игры
            game_options = {f"{game_name} (ID: {game_id})": game_id for game_id, game_name in games}
            selected_game = st.selectbox("Выберите игру", options=list(game_options.keys()))
            game_id = game_options[selected_game]

            # Выбор локации
            location_options = {f"{location_name}, {location_address} (ID: {location_id})": location_id for location_id, location_name, location_address in locations}
            selected_location = st.selectbox("Выберите локацию", options=list(location_options.keys()))
            location_id = location_options[selected_location]

            # Ввод количества копий
            num_copies = st.number_input("Количество копий для добавления", min_value=1, step=1)

            # Кнопка добавления
            if st.button("Добавить копии"):
                try:
                    next_copy_id = get_next_copy_id()
                    if next_copy_id is None:
                        st.error("Ошибка при генерации copy_id.")
                        return

                    with get_connection() as conn:
                        with conn.cursor() as cur:
                            # Генерация уникальных copy_id и добавление копий
                            for i in range(num_copies):
                                copy_id = next_copy_id + 1 + i
                                cur.execute("""
                                    INSERT INTO copies (copy_id, game_id, status, location_id)
                                    VALUES (%s, %s, 'Available', %s)
                                """, (copy_id, game_id, location_id))

                            conn.commit()
                            st.success(f"{num_copies} копий игры успешно добавлены в локацию.")
                except Exception as e:
                    st.error(f"Ошибка при добавлении копий игры: {e}")
        else:
            st.info("Нет доступных игр или локаций.")
    except Exception as e:
        st.error(f"Ошибка при загрузке данных: {e}")

