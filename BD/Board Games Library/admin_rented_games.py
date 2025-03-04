import streamlit as st
from database import get_connection
from finish_rental import add_finish_buttons  # Импортируем функцию для завершения аренды

def display_admin_rented_games():
    st.title("Список арендованных настольных игр")

    # Переключение между режимами просмотра
    view_mode = st.radio(
        "Выберите режим просмотра:",
        ["Все аренды", "Аренды от конкретного пользователя", "Аренды конкретной игры"]
    )

    try:
        with get_connection() as conn:
            with conn.cursor() as cur:
                if view_mode == "Все аренды":
                    # Получение всех аренд
                    cur.execute("""
                        SELECT r.rental_id, g.game_name, c.copy_id, cl.name, cl.email, r.start_date, r.end_date
                        FROM rentals r
                        JOIN copies c ON r.copy_id = c.copy_id
                        JOIN games g ON c.game_id = g.game_id
                        JOIN clients cl ON r.client_id = cl.client_id
                        ORDER BY r.start_date DESC
                    """)
                    rented_games = cur.fetchall()

                    if rented_games:
                        st.write("### Все текущие аренды")
                        add_finish_buttons(rented_games)  # Добавляем кнопки "Закончить"
                    else:
                        st.info("На данный момент арендованных игр нет.")

                elif view_mode == "Аренды от конкретного пользователя":
                    # Получение списка клиентов
                    cur.execute("""
                        SELECT client_id, name, email 
                        FROM clients 
                        WHERE name IS NOT NULL AND email IS NOT NULL AND name != '' AND email != ''
                    """)
                    clients = cur.fetchall()
                    client_dict = {f"{name} ({email})": client_id for client_id, name, email in clients}

                    if clients:
                        selected_client = st.selectbox("Выберите клиента:", list(client_dict.keys()))

                        if selected_client:
                            client_id = client_dict[selected_client]
                            # Получение аренд для выбранного клиента
                            cur.execute("""
                                SELECT r.rental_id, g.game_name, c.copy_id, cl.name, cl.email, r.start_date, r.end_date
                                FROM rentals r
                                JOIN copies c ON r.copy_id = c.copy_id
                                JOIN games g ON c.game_id = g.game_id
                                JOIN clients cl ON r.client_id = cl.client_id
                                WHERE r.client_id = %s
                                ORDER BY r.start_date DESC
                            """, (client_id,))
                            client_rentals = cur.fetchall()

                            if client_rentals:
                                st.write(f"### Аренды пользователя: {selected_client}")
                                add_finish_buttons(client_rentals)  # Добавляем кнопки "Закончить"
                            else:
                                st.info(f"У пользователя {selected_client} нет активных аренд.")
                    else:
                        st.info("Нет зарегистрированных клиентов.")

                elif view_mode == "Аренды конкретной игры":
                    # Получение списка игр
                    cur.execute("SELECT game_id, game_name FROM games")
                    games = cur.fetchall()
                    game_dict = {game_name: game_id for game_id, game_name in games}

                    if games:
                        selected_game = st.selectbox("Выберите игру:", list(game_dict.keys()))

                        if selected_game:
                            game_id = game_dict[selected_game]
                            # Получение аренд для выбранной игры
                            cur.execute("""
                                SELECT r.rental_id, g.game_name, c.copy_id, cl.name, cl.email, r.start_date, r.end_date
                                FROM rentals r
                                JOIN copies c ON r.copy_id = c.copy_id
                                JOIN games g ON c.game_id = g.game_id
                                JOIN clients cl ON r.client_id = cl.client_id
                                WHERE g.game_id = %s
                                ORDER BY r.start_date DESC
                            """, (game_id,))
                            game_rentals = cur.fetchall()

                            if game_rentals:
                                st.write(f"### Аренды игры: {selected_game}")
                                add_finish_buttons(game_rentals)  # Добавляем кнопки "Закончить"
                            else:
                                st.info(f"На игру {selected_game} нет активных аренд.")
                    else:
                        st.info("Нет доступных игр.")

    except Exception as e:
        st.error(f"Ошибка при получении данных об арендах: {e}")

