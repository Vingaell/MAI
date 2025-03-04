import streamlit as st
from database import get_connection

def finish_rental(rental_id, copy_id):
    """
    Функция для завершения аренды: удаляет аренду из таблицы rentals
    и изменяет статус копии игры на 'Available'.
    """
    try:
        with get_connection() as conn:
            with conn.cursor() as cur:
                # Удаление аренды
                cur.execute("DELETE FROM rentals WHERE rental_id = %s", (rental_id,))
                # Обновление статуса копии игры
                cur.execute("UPDATE copies SET status = 'Available' WHERE copy_id = %s", (copy_id,))
                conn.commit()
                st.success(f"Аренда ID {rental_id} успешно завершена.")
    except Exception as e:
        st.error(f"Ошибка при завершении аренды: {e}")

def add_finish_buttons(rentals):
    """
    Добавляет кнопки "Закончить" рядом с каждой записью аренды.
    """
    for rental in rentals:
        rental_id, game_name, copy_id, client_name, client_email, start_date, end_date = rental
        st.write(f"**Игра**: {game_name} (ID копии: {copy_id})")
        st.write(f"**Клиент**: {client_name} ({client_email})")
        st.write(f"**Срок аренды**: с {start_date} по {end_date}")
        if st.button(f"Закончить аренду {rental_id}", key=f"finish_{rental_id}"):
            finish_rental(rental_id, copy_id)
        st.write("---")
