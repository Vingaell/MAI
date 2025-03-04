import bcrypt
import streamlit as st
from database import get_connection

def login_user():
    st.subheader("Вход в систему")
    username = st.text_input("Имя пользователя")
    password = st.text_input("Пароль", type="password")
    login_button = st.button("Войти")

    if login_button:
        try:
            with get_connection() as conn:
                with conn.cursor() as cur:
                    cur.execute("SELECT user_id, password, user_type FROM users WHERE username = %s", (username,))
                    result = cur.fetchone()

                    if result and bcrypt.checkpw(password.encode('utf-8'), result[1].encode('utf-8')):
                        st.success("Успешный вход!")

                        # Сохраняем данные о пользователе в session_state
                        st.session_state.authenticated = True
                        st.session_state.user_type = result[2]
                        st.session_state.username = username
                        st.session_state.user_id = result[0]

                        # Перезагружаем приложение
                        st.rerun()
                    else:
                        st.error("Неверное имя пользователя или пароль.")
        except Exception as e:
            st.error(f"Ошибка входа: {e}")



def register_user():
    st.subheader("Регистрация клиента")
    username = st.text_input("Имя пользователя (уникальное)", key="reg_username")
    password = st.text_input("Пароль", type="password", key="reg_password")
    confirm_password = st.text_input("Подтвердите пароль", type="password", key="reg_confirm_password")
    register_button = st.button("Зарегистрироваться")

    if register_button:
        if password != confirm_password:
            st.error("Пароли не совпадают!")
            return

        try:
            hashed_password = bcrypt.hashpw(password.encode('utf-8'), bcrypt.gensalt()).decode('utf-8')
            with get_connection() as conn:
                with conn.cursor() as cur:
                    # Проверка уникальности имени пользователя
                    cur.execute("SELECT COUNT(*) FROM users WHERE username = %s", (username,))
                    if cur.fetchone()[0] > 0:
                        st.error("Имя пользователя уже занято.")
                        return
                    
                    # Получение нового user_id
                    cur.execute("SELECT COALESCE(MAX(user_id), 0) + 1 FROM users")
                    user_id = cur.fetchone()[0]

                    # Вставка нового пользователя в таблицу users
                    cur.execute("""
                        INSERT INTO users (user_id, username, password, user_type)
                        VALUES (%s, %s, %s, %s)
                    """, (user_id, username, hashed_password, "client"))
                    conn.commit()

                    # Теперь создаем пустую запись в таблице clients
                    # Получаем user_id для текущего пользователя
                    cur.execute("SELECT user_id FROM users WHERE username = %s", (username,))
                    user_id = cur.fetchone()[0]

                    # Генерируем новый client_id
                    cur.execute("SELECT COALESCE(MAX(client_id), 0) + 1 FROM clients")
                    new_client_id = cur.fetchone()[0]

                    # Вставляем пустую запись в таблицу clients
                    cur.execute("""
                        INSERT INTO clients (client_id, user_id, name, phone_number, client_address, email, birth_date)
                        VALUES (%s, %s, NULL, NULL, NULL, NULL, NULL)
                    """, (new_client_id, user_id))
                    conn.commit()

                    st.success("Регистрация завершена! Теперь вы можете войти в систему.")
        except Exception as e:
            st.error(f"Ошибка регистрации: {e}")




