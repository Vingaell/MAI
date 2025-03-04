import streamlit as st
from database import get_connection

def delete_game():
    st.subheader("Удаление игры")
    
    try:
        with get_connection() as conn:
            with conn.cursor() as cur:
                # Получаем список игр
                cur.execute("SELECT game_id, game_name FROM games")
                games = cur.fetchall()

        if games:
            game_options = {f"{game_name} (ID: {game_id})": game_id for game_id, game_name in games}
            selected_game = st.selectbox("Выберите игру для удаления", options=list(game_options.keys()))

            if st.button("Удалить игру"):
                game_id = game_options[selected_game]

                try:
                    with get_connection() as conn:
                        with conn.cursor() as cur:
                            # Проверяем, есть ли копии игры в таблице copies
                            cur.execute("SELECT COUNT(*) FROM copies WHERE game_id = %s", (game_id,))
                            count = cur.fetchone()[0]

                            if count > 0:
                                st.warning("Невозможно удалить игру, так как у неё есть копии в наличии.")
                            else:
                                # Удаляем связи игры с тегами
                                cur.execute("DELETE FROM games_to_tags WHERE game_id = %s", (game_id,))
                                # Удаляем игру
                                cur.execute("DELETE FROM games WHERE game_id = %s", (game_id,))
                                conn.commit()
                                st.success(f"Игра с ID {game_id} успешно удалена.")
                except Exception as e:
                    st.error(f"Ошибка при удалении игры: {e}")
        else:
            st.info("Нет доступных игр для удаления.")
    except Exception as e:
        st.error(f"Ошибка при загрузке данных об играх: {e}")
