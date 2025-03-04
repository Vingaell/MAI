import streamlit as st
from database import get_connection

def display_game_list():
    try:
        with get_connection() as conn:
            with conn.cursor() as cur:
                # Получаем список игр с возрастным рейтингом, минимальным/максимальным количеством игроков, тегами и годом выпуска
                cur.execute("""
                    SELECT g.game_id, g.game_name, g.release_year, g.play_time, 
                           g.min_players, g.max_players, g.age_rating,
                           array_agg(DISTINCT t.name) AS tags, 
                           array_agg(DISTINCT t.description) AS tag_descriptions
                    FROM games g
                    JOIN games_to_tags gt ON g.game_id = gt.game_id
                    JOIN tags t ON gt.tag_id = t.tag_id
                    GROUP BY g.game_id
                """)
                games_data = cur.fetchall()

                if games_data:
                    # Создаем два столбца: для игр и для тегов
                    col1, col2 = st.columns([3, 1])

                    with col1:
                        st.write("### Список игр")
                        for game in games_data:
                            game_id, game_name, release_year, play_time, min_players, max_players, age_rating, tags, tag_descriptions = game
                            st.write(f"**{game_name}** ({release_year})")
                            st.write(f"- **Игроки:** от {min_players} до {max_players}")
                            st.write(f"- **Время игры:** {play_time} мин")
                            st.write(f"- **Возрастной рейтинг:** {age_rating}+")
                            st.write(f"- **Теги:** {', '.join(tags)}")
                            st.write("---")

                    with col2:
                        st.write("### Описание тегов")
                        # Множество для хранения уже выведенных тегов, чтобы избежать повторений
                        displayed_tags = set()
                        for game in games_data:
                            _, _, _, _, _, _, _, tags, tag_descriptions = game
                            # Для каждого тега выводим его описание, если он еще не был выведен
                            for tag_name, tag_description in zip(tags, tag_descriptions):
                                if tag_name not in displayed_tags:
                                    st.write(f"**{tag_name}**: {tag_description}")
                                    displayed_tags.add(tag_name)

                else:
                    st.write("Нет доступных игр.")
    except Exception as e:
        st.error(f"Ошибка при получении списка игр: {e}")
