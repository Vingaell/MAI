import streamlit as st
from database import get_connection
import datetime

# Функция для получения следующего rental_id
def get_next_rental_id():
    try:
        with get_connection() as conn:
            with conn.cursor() as cur:
                cur.execute("SELECT COALESCE(MAX(rental_id), 0) + 1 FROM rentals")
                next_rental_id = cur.fetchone()[0]
                return next_rental_id
    except Exception as e:
        st.error(f"Ошибка при генерации rental_id: {e}")
        return None

# Функция для отображения доступных игр для аренды
def display_game_rentals(username):
    try:
        # Получаем client_id по имени пользователя
        with get_connection() as conn:
            with conn.cursor() as cur:
                cur.execute("""
                    SELECT cl.client_id
                    FROM clients cl
                    JOIN users u ON cl.user_id = u.user_id
                    WHERE u.username = %s
                """, (username,))
                client_data = cur.fetchone()
                if not client_data:
                    st.error("Не удалось найти клиента, связанного с этим пользователем.")
                    return
                client_id = client_data[0]

                # Получаем игры с доступными копиями
                cur.execute("""
                    SELECT g.game_id, g.game_name, l.location_id, l.location_name, l.location_address,
                           COUNT(c.copy_id) AS total_copies,
                           COUNT(CASE WHEN c.status = 'Available' THEN 1 END) AS available_copies
                    FROM games g
                    JOIN copies c ON g.game_id = c.game_id
                    JOIN locations l ON c.location_id = l.location_id
                    GROUP BY g.game_id, l.location_id, l.location_name, l.location_address
                    ORDER BY g.game_name, l.location_name
                """)
                games_data = cur.fetchall()

                if games_data:
                    for game in games_data:
                        game_id, game_name, location_id, location_name, location_address, total_copies, available_copies = game

                        st.write(f"### {game_name} ({location_name})")
                        st.write(f"Адрес: {location_address}")
                        st.write(f"Общее количество копий: {total_copies}")
                        st.write(f"Доступные копии: {available_copies}")

                        if available_copies > 0:
                            # Кнопка аренды
                            with st.form(f"rental_form_{game_id}_{location_id}"):
                                rental_duration = st.selectbox("Выберите срок аренды (дней):", range(1, 16))
                                submit_button = st.form_submit_button("Ок")

                                # Проверим, если форма отправлена
                                if submit_button:
                                    # Проверим, выбран ли срок аренды
                                    if rental_duration:
                                        # Получаем доступную копию
                                        with get_connection() as conn:
                                            with conn.cursor() as cur:
                                                cur.execute("""
                                                    SELECT copy_id 
                                                    FROM copies 
                                                    WHERE game_id = %s AND location_id = %s AND status = 'Available'
                                                    LIMIT 1
                                                """, (game_id, location_id))
                                                available_copy = cur.fetchone()

                                                if available_copy:
                                                    copy_id = available_copy[0]
                                                    rental_id = get_next_rental_id()

                                                    if rental_id:
                                                        start_date = datetime.date.today()
                                                        end_date = start_date + datetime.timedelta(days=rental_duration)

                                                        # Обновление статуса копии на 'Rented' и добавление аренды
                                                        cur.execute("""
                                                            UPDATE copies
                                                            SET status = 'Rented'
                                                            WHERE copy_id = %s
                                                        """, (copy_id,))

                                                        # Вставка новой аренды в таблицу rentals
                                                        cur.execute("""
                                                            INSERT INTO rentals (rental_id, copy_id, start_date, end_date, client_id)
                                                            VALUES (%s, %s, %s, %s, %s)
                                                        """, (rental_id, copy_id, start_date, end_date, client_id))
                                                        conn.commit()

                                                        # Пересчитываем доступные копии
                                                        cur.execute("""
                                                            SELECT COUNT(CASE WHEN status = 'Available' THEN 1 END) AS available_copies
                                                            FROM copies
                                                            WHERE game_id = %s AND location_id = %s
                                                        """, (game_id, location_id))
                                                        available_copies_after = cur.fetchone()[0]

                                                        st.success(f"Игра {game_name} успешно арендована на {rental_duration} дней.")
                                                        st.write(f"Теперь доступных копий: {available_copies_after}")
                                                else:
                                                    st.warning("Нет доступных копий для аренды в этой локации.")
                                    else:
                                        st.warning("Выберите срок аренды.")
                        else:
                            st.warning(f"В локации {location_name} нет доступных копий игры {game_name}.")
                else:
                    st.warning("Нет доступных игр для аренды.")
    except Exception as e:
        st.error(f"Ошибка при обработке запроса: {e}")


















