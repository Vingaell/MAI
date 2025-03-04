import streamlit as st
from database import get_connection

def display_copies_count():
    st.title("Количество копий игр в различных местах")

    try:
        with get_connection() as conn:
            with conn.cursor() as cur:
                # Запрос для подсчета общего количества копий и доступных копий
                cur.execute("""
                    SELECT 
                        g.game_name, 
                        l.location_name, 
                        COUNT(c.copy_id) AS total_copies,
                        SUM(CASE WHEN c.status = 'Available' THEN 1 ELSE 0 END) AS available_copies
                    FROM copies c
                    JOIN games g ON c.game_id = g.game_id
                    JOIN locations l ON c.location_id = l.location_id
                    GROUP BY g.game_name, l.location_name
                    ORDER BY g.game_name, l.location_name
                """)
                results = cur.fetchall()

                if results:
                    st.write("### Количество копий по играм и местам:")
                    for game_name, location_name, total_copies, available_copies in results:
                        st.write(f"- **{game_name}** в локации **{location_name}**: "
                                 f"{total_copies} копий (Доступных: {available_copies})")
                else:
                    st.info("Данные о копиях отсутствуют.")

    except Exception as e:
        st.error(f"Ошибка при получении данных: {e}")
