import streamlit as st
from database import get_connection
import pandas as pd

def display_rented_games(username):
    try:
        with get_connection() as conn:
            with conn.cursor() as cur:
                # Получаем client_id по имени пользователя
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

                # Получаем список арендованных игр текущего пользователя
                cur.execute("""
                    SELECT g.game_name, r.start_date, r.end_date, l.location_name, l.location_address
                    FROM rentals r
                    JOIN copies c ON r.copy_id = c.copy_id
                    JOIN games g ON c.game_id = g.game_id
                    JOIN locations l ON c.location_id = l.location_id
                    WHERE r.client_id = %s
                    ORDER BY r.start_date DESC
                """, (client_id,))
                rented_games = cur.fetchall()

                if rented_games:
                    st.write("### Ваши арендованные игры:")
                    for game in rented_games:
                        game_name, start_date, end_date, location_name, location_address = game
                        st.write(f"**{game_name}**")
                        st.write(f"- **Дата начала аренды:** {start_date.strftime('%d-%m-%Y')}")
                        st.write(f"- **Дата окончания аренды:** {end_date.strftime('%d-%m-%Y')}")
                        st.write(f"- **Локация:** {location_name}")
                        st.write(f"- **Адрес локации:** {location_address}")
                        st.write("---")
                else:
                    st.write("У вас нет арендованных игр.")
    except Exception as e:
        st.error(f"Ошибка при получении списка арендованных игр: {e}")

