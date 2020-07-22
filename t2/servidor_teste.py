import socket

# Configuracao do socket
socket_servidor = socket.socket()

# Entrada de endereco IP
entrada_endereco = str(input("Endereco (use lcl para transferencia local): "))

# Entrada de porta
porta = int(input("Porta: "))

# Se a entrada for "lcl" -> endereco = hostname
if(entrada_endereco == "lcl"):
    endereco = socket.gethostname()
else:
    endereco = entrada_endereco

# Liga o socket a tupla endereco porta
socket_servidor.bind((endereco, porta))

# Pode receber ate 5 conexoes
socket_servidor.listen(5)
while True:
    socket_cliente, endereco_cliente = socket_servidor.accept()
    print("Conexao com o cliente " + str(endereco_cliente[0]))
    socket_cliente.close()