import streamlit as st
from database import get_connection

def display_client_data(username):
    try:
        with get_connection() as conn:
            with conn.cursor() as cur:
                # Получаем данные пользователя из таблицы "clients"
                cur.execute("""
                    SELECT client_id, name, phone_number, client_address, email, birth_date 
                    FROM clients 
                    WHERE user_id = (SELECT user_id FROM users WHERE username = %s)
                """, (username,))
                result = cur.fetchone()

                if result:
                    # Если данные уже есть, отображаем их и предоставляем возможность редактировать
                    client_id = result[0]
                    name = st.text_input("Имя", value=result[1], key="name")
                    phone_number = st.text_input("Телефон", value=result[2], key="phone_number")
                    client_address = st.text_input("Адрес", value=result[3], key="client_address")
                    email = st.text_input("Email", value=result[4], key="email")
                    birth_date = st.date_input("Дата рождения", value=result[5], key="birth_date")

                    if st.button("Сохранить изменения"):
                        # Логика для сохранения изменений в базе данных
                        cur.execute("""
                            UPDATE clients
                            SET name = %s, phone_number = %s, client_address = %s, email = %s, birth_date = %s
                            WHERE client_id = %s
                        """, (name, phone_number, client_address, email, birth_date, client_id))
                        conn.commit()
                        st.success("Данные успешно обновлены.")
                else:
                    st.warning("Вы еще не заполнили свои персональные данные.")
    except Exception as e:
        st.error(f"Ошибка: {e}")
