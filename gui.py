# 25-jun-24
# Del GUI de lo que regresa hanoi.c para proyecto final
import time
from tkinter import * #Módulo para visual completo
from tkinter import messagebox # si necesitamos este aparte para caso no 1-8

# Crear la ventana principal de Tkinter
raiz = Tk()
raiz.title("Torres de Hanoi")

# Obtener las dimensiones de la pantalla
ancho_pantalla = raiz.winfo_screenwidth()
alto_pantalla = raiz.winfo_screenheight()

# Ajustar el tamaño de la ventana a las dimensiones de la pantalla
raiz.geometry(f"{ancho_pantalla}x{alto_pantalla}")

# Definir canvas que ocupará toda la pantalla
lienzo = Canvas(raiz, width=ancho_pantalla, height=alto_pantalla - 100, bg="linen")
lienzo.pack()

# Variables para las posiciones de las pilas en el canvas
posiciones_pilas = {
    "A": ancho_pantalla // 6.5,# Que tanto a la izq. el A,mayor número más izquierda
    "B": ancho_pantalla // 2, # sobre dos para mitad
    "C": 2.5 * ancho_pantalla // 3 #dejar entre 3 y 4 o se pone raro
}
altura_pila = alto_pantalla - 350 #De abajo a arriba, mover toda la torre
altura_disco = 40

# Se crea un dicionario(tabla hash) de listas.
discos = {
    "A": [],
    "B": [],
    "C": []
}

etiquetas_discos = ["destino", "auxiliar"] * 4 #MODIFCIABLE PARA AUMENTAR
colores_discos = ["hotPink", "green", "dark turquoise", "DodgerBlue4", "DeepSkyBlue", "purple", "red", "DarkGoldenrod1"] #MODIFCIABLE PARA AUMENTAR

def dibujar_pilas():# :/ O(n)
    for pila, x in posiciones_pilas.items():# De pila en pila
        lienzo.create_line(x, altura_pila, x, altura_pila - 350, width=5, fill="black")#palitos
        for i, (ancho_disco, etiqueta, color) in enumerate(discos[pila]):# Disco por disco
            lienzo.create_rectangle(x - ancho_disco, altura_pila - (i + 1) * altura_disco,
                                    x + ancho_disco, altura_pila - i * altura_disco,
                                    fill=color)
            lienzo.create_text(x, altura_pila - (i + 0.5) * altura_disco, text=etiqueta, fill="white", font=("Arial", 30))

def actualizar_pilas():#borra-dibuja en cada "movimiento" :/ O(n)
    lienzo.delete("all")
    dibujar_pilas()

def mover_disco_visual(origen, destino, pila_origen, pila_destino): # :/ O(n)
    disco = discos[pila_origen].pop()#con la funcion interna de python
    discos[pila_destino].append(disco)#push con base en el movi.txt
    actualizar_pilas()#Del actualziar para el "movimiento"
    raiz.update()
    time.sleep(1) # Velocidad "movimientos"

# Mapear números a letras, para que el hash-list reconozca 1 como A,etc.
mapa_pilas = {
    '1': 'A',
    '2': 'B',
    '3': 'C'
}

def ejecutar_movimientos_desde_archivo(nombre_archivo): # :/ O(m * n)
    with open(nombre_archivo, 'r') as archivo:
        movimientos = archivo.readlines()
    #lee de arriba a abajo de izquierda a derecha en: 1 2
                                                    # 2 3
    
    for movimiento in movimientos:
        origen, destino = movimiento.strip().split()#separa para poder leer lo del .txt 
        # Convertir números a letras
        origen = mapa_pilas[origen]
        destino = mapa_pilas[destino]
        mover_disco_visual(origen, destino, origen, destino)#aplic ael movimiento

def inicializar_discos(n): # :/ O(n)
    discos["A"].clear()
    discos["B"].clear()
    discos["C"].clear()

    for i in range(n, 0, -1):#para tomar en reversa para de base a punta
        #si n=5 => 5,4,3,2,1, es de donde a donde con saltos de 
        discos["A"].append((i * 25, etiquetas_discos[i-1], colores_discos[i-1]))#MODIFICABLE AUMENTAR
        #del largo de los discos 25,a mayor mas largo, toma etiquetas y
        #toma color de las listas anteriores
    actualizar_pilas()
    raiz.update()
    time.sleep(5)# espera desde estado inicial 

def iniciar_hanoi():# GUI para ininicar # :/ O(m * n)
    try:
        n = int(entrada_discos.get())
        nombre_archivo = entrada_archivo.get()
        if 1 <= n <= 8:#MODIFICABLE PARA AUMENTAR
            inicializar_discos(n)
            ejecutar_movimientos_desde_archivo(nombre_archivo)
        else:
            messagebox.showerror("Error", "Por favor ingrese un número entre 1 y 8.")
    except ValueError:
        messagebox.showerror("Error", "Por favor ingrese un número válido.")

marco_controles = Frame(raiz) #literal de crear un marco al rededor de la ventana
marco_controles.pack()

# Del ingresar datos para discos
etiqueta_entrada_discos = Label(marco_controles, text="Número de discos (1-8):")#Del "boton" reglas
etiqueta_entrada_discos.pack(side=LEFT)#ubicacion de empaquetado
entrada_discos = Entry(marco_controles)#De donde ingresar el numero
entrada_discos.pack(side=LEFT)#ubicación de empaquetado

# Del ingresar datos movi.txt
etiqueta_entrada_archivo = Label(marco_controles, text="Archivo de movimientos:")
etiqueta_entrada_archivo.pack(side=LEFT)
entrada_archivo = Entry(marco_controles)
entrada_archivo.pack(side=LEFT)

# Del boton de inicio
boton_iniciar = Button(marco_controles, text="Iniciar", command=iniciar_hanoi)
boton_iniciar.pack(side=LEFT)

# Constantemente espera clics en la ventana
raiz.mainloop()

# Por Said Carbot et all.
# México-IPN-ESCOM,junio 2024
