import streamlit as st
from authentication import login_user, register_user
from client_dashboard import display_client_dashboard
from admin_dashboard import display_admin_dashboard  # Импортируем новый файл для админки

def main():
    st.title("Библиотека настольных игр")
    
    # Проверка состояния аутентификации
    if "authenticated" not in st.session_state:
        st.session_state.authenticated = False
        st.session_state.user_type = None
        st.session_state.username = None

    if not st.session_state.authenticated:
        st.subheader("Добро пожаловать!")
        choice = st.selectbox("Выберите действие", ["Вход", "Регистрация"])

        if choice == "Вход":
            login_user()  # Пользователь входит, после чего перенаправляется
        elif choice == "Регистрация":
            register_user()  # Регистрация пользователя
        else:
            st.warning("чикиряу")
    else:
        if st.session_state.user_type == "client":
            # Показываем личный кабинет клиента
            display_client_dashboard(st.session_state.username)  # Вызов функции для отображения личного кабинета
        elif st.session_state.user_type == "admin":
            # Перенаправляем администратора на страницу администрирования
            display_admin_dashboard()  # Вызов функции для отображения панели администратора
        else:
            st.warning("Неизвестный тип пользователя")

if __name__ == "__main__":
    main()




