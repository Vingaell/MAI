import streamlit as st
from database import get_connection

def display_clients_list():
    """Функция для отображения списка всех клиентов."""
    st.title("Список пользователей")

    try:
        with get_connection() as conn:
            with conn.cursor() as cur:
                # Запрос для получения данных о клиентах
                cur.execute("""
                    SELECT u.username, 
                           c.name, 
                           c.phone_number, 
                           c.client_address, 
                           c.email, 
                           c.birth_date
                    FROM users u
                    JOIN clients c ON u.user_id = c.user_id
                """)
                clients_data = cur.fetchall()

                if clients_data:
                    for client in clients_data:
                        username, name, phone_number, client_address, email, birth_date = client
                        st.write(f"**Пользователь:** {username}")
                        st.write(f"- **Имя:** {name or 'информация отсутствует'}")
                        st.write(f"- **Телефон:** {phone_number or 'информация отсутствует'}")
                        st.write(f"- **Адрес:** {client_address or 'информация отсутствует'}")
                        st.write(f"- **Электронная почта:** {email or 'информация отсутствует'}")
                        st.write(f"- **Дата рождения:** {birth_date or 'информация отсутствует'}")
                        st.write("---")
                else:
                    st.info("На данный момент зарегистрированных пользователей нет.")
    except Exception as e:
        st.error(f"Ошибка при получении данных о пользователях: {e}")
