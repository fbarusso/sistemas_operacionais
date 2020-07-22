import socket
import threading
import random

def requisicao(endereco, porta):
	# Configuracao do socket
	socket_cliente = socket.socket()

	# Se conecta com a tupla endereco porta
	socket_cliente.connect((endereco, porta))
	print("Conexao com o servidor " + str(endereco));

	valor_requisicao = random.randint(1, 2000)
	socket_cliente.send(str(valor_requisicao).encode())
	print("Requisicao: " + str(valor_requisicao))

	resultado = socket_cliente.recv(1024)
	print("Resultado: " + resultado.decode())

	# Encerra a conexao
	socket_cliente.close()
	print("Fim da conexao com o servidor " + str(endereco))

# Lista de threads
lista_threads = []

# Entrada de endereco IP
entrada_endereco = str(input("Endereco (use lcl para transferencia local): "))

# Entrada de porta
porta = int(input("Porta: "))

# Numero de threads
numero_threads = int(input("Numero de threads: "))

# Se a entrada for "lcl" -> endereco = hostname
if(entrada_endereco == "lcl"):
	endereco = socket.gethostname()
else:
	endereco = entrada_endereco

# Criacao das threads
for i in range(0, numero_threads):
	lista_threads.append(threading.Thread(target=requisicao, args=(endereco, porta)))
	print("nova thread em lista_threads[" + str(i) + "]")

# Inicio das threads
for i in range(0, numero_threads):
	lista_threads[i].start()

# A thread principal aguarda o fim das threads criadas
for i in range(0, numero_threads):
	lista_threads[i].join()
