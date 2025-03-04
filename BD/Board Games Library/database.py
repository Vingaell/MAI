import psycopg2
import os
from psycopg2.extras import RealDictCursor

def get_connection():
    return psycopg2.connect(
        host="localhost",
        database="board_games",
        user="postgres",
        password="123"
    )

