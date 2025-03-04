import streamlit as st
from database import get_connection
import pandas as pd
from datetime import datetime
from client_data import display_client_data
from game_list import display_game_list
from rent_game import display_game_rentals
from rented_games import display_rented_games

min_birth_date = datetime(1900, 1, 1)
max_birth_date = datetime.today()

# Страница с личной информацией и арендами
def display_client_dashboard(username):
    st.sidebar.title("Навигация")
    menu = st.sidebar.radio("Выберите действие:", 
                             ["Главная", "Личные данные", "Список игр", 
                              "Мой список арендованных игр", "Арендовать настольную игру", "Выход"], 
                             index=0)

    if menu == "Главная":
        st.write("Добро пожаловать в ваш личный кабинет! Выберите действие в меню слева.")
    
    elif menu == "Личные данные":
        display_client_data(username)
    
    elif menu == "Список игр":
        display_game_list()

    elif menu == "Мой список арендованных игр":
        display_rented_games(username)

    elif menu == "Арендовать настольную игру":
        try:
            with get_connection() as conn:
                with conn.cursor() as cur:
                    cur.execute("""
                        SELECT name, phone_number, client_address, email, birth_date 
                        FROM clients 
                        WHERE user_id = (SELECT user_id FROM users WHERE username = %s)
                    """, (username,))
                    result = cur.fetchone()

                    # Проверяем, есть ли NULL в персональных данных
                    if result and all(result):
                        display_game_rentals(username)
                    else:
                        st.error("Пожалуйста, заполните все свои личные данные, чтобы арендовать настольную игру.")
        except Exception as e:
            st.error(f"Ошибка: {e}")

    elif menu == "Выход":
        # Выход из системы
        st.session_state.authenticated = False
        st.session_state.user_type = None
        st.session_state.username = None
        st.session_state.user_id = None
        st.rerun()

# Страница для редактирования личных данных
def edit_personal_info(username):
    st.title("Редактирование личных данных")

    try:
        with get_connection() as conn:
            with conn.cursor() as cur:
                # Получаем текущие данные клиента
                cur.execute("SELECT name, phone_number, client_address, email, birth_date FROM clients WHERE user_id = (SELECT user_id FROM users WHERE username = %s)", (username,))
                client_data = cur.fetchone()

                if client_data:
                    # Заполняем форму с текущими данными
                    name = st.text_input("Имя", client_data[0])
                    phone = st.text_input("Телефон", client_data[1])
                    address = st.text_input("Адрес", client_data[2])
                    email = st.text_input("Email", client_data[3])
                    birth_date = st.date_input("Дата рождения", client_data[4])

                    if st.button("Сохранить изменения"):
                        # Обновление данных в базе
                        cur.execute("""
                            UPDATE clients 
                            SET name = %s, phone_number = %s, client_address = %s, email = %s, birth_date = %s
                            WHERE user_id = (SELECT user_id FROM users WHERE username = %s)
                        """, (name, phone, address, email, birth_date, username))
                        conn.commit()
                        st.success("Ваши данные успешно обновлены!")
                else:
                    # Если данных нет, показываем форму для их ввода
                    name = st.text_input("Имя")
                    phone = st.text_input("Телефон")
                    address = st.text_input("Адрес")
                    email = st.text_input("Email")
                    birth_date = st.date_input("Дата рождения")

                    if st.button("Сохранить данные"):
                        # Вставка данных в базу
                        cur.execute("""
                            INSERT INTO clients (user_id, name, phone_number, client_address, email, birth_date)
                            VALUES ((SELECT user_id FROM users WHERE username = %s), %s, %s, %s, %s, %s)
                        """, (username, name, phone, address, email, birth_date))
                        conn.commit()
                        st.success("Ваши данные успешно сохранены!")
    except Exception as e:
        st.error(f"Ошибка обновления данных: {e}")

