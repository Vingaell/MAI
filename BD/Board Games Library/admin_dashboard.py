import streamlit as st
from add_game import display_add_game_form
from delete_game import delete_game
from add_copies import add_game_copies
from game_list import display_game_list  # Подключение файла для списка игр
from admin_rented_games import display_admin_rented_games 
from show_copies_count import display_copies_count
from display_clients import display_clients_list 

# Функция для отображения панели администратора
def display_admin_dashboard():
    st.sidebar.title("Панель администратора")  # Заголовок в боковой панели

    # Список действий администратора
    menu = st.sidebar.radio("Выберите действие:", 
                             ["Главная", "Добавить копии игры", "Добавить новую игру", "Показать количество копий", 
                              "Удалить игру", "Список игр", "Список пользователей", "Список арендованных настольных игр", 
                               "Выход"], index=0)

    if menu == "Главная":
        st.write("Добро пожаловать в панель администратора! Выберите действие в меню слева.")
    
    elif menu == "Добавить копии игры":
        add_game_copies()
    
    elif menu == "Добавить новую игру":
        display_add_game_form()  # Вызов функции для добавления игры

    elif menu == "Удалить игру":
        delete_game()

    elif menu == "Список игр":
        display_game_list()  # Вызов функции для отображения списка игр

    elif menu == "Список арендованных настольных игр":
        display_admin_rented_games() 

    elif menu == "Показать количество копий":
        display_copies_count()

    elif menu == "Список пользователей":
        display_clients_list()

    elif menu == "Выход":
        # Выход из системы
        st.session_state.authenticated = False
        st.session_state.user_type = None
        st.session_state.username = None
        st.session_state.user_id = None
        st.rerun()

