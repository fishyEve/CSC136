#!/usr/bin/env python3

#Author: Eve Collier
#Assignment: Network Program: Chat Server 
#Course: CSC 328 section 010
#Fall 2023

import select
import socket
import sys
import os
import signal
from library import sendingPromptMessage
from library import totallyReadingText
from library import sendingChats
#from library import totallyReadingChats


# Function Name: clientChat
# Decription: Allows client to send messages to server
# Parameters: footSocks - the socket created upon connection to the server
#
# Return value: none
def clientChat(footSocks, nickname):
	print("in chat")
	socks_in_drawer = [sys.stdin, footSocks]
	while True:
		try:
			read_sockets, write_sockets, error_sockets = select.select(socks_in_drawer, [], []) # ADDED 12/12
			for sock in read_sockets: # ADDED 12/12
				if sock == footSocks:	  # ADDED 12/12
					# we are getting a message
					sockMsg = totallyReadingText(sock) # ADDED 12/12
					print(sockMsg) #print(nickname + ": " + sockMsg)
				else:
					msg = sys.stdin.readline()	# user has entered a message
					footSocks.sendall(sendingPromptMessage(msg))
					#footSocks.sendall(sendingChats(nickname, msg))
		except KeyboardInterrupt:
			footSocks.sendall(sendingPromptMessage("BYE"))
			print(" You are now leaving Cookie Chat! Have a sweet day!")	
			footSocks.close()
			sock.close()
			sys.exit(-1)


	#end of clientChat


# Function Name: main
# Main function for the client side
# Parameters: none
# Return value: none
if __name__ == "__main__":
	# accept two command line arguments, the host and the port
	cmdArgs = len(sys.argv)
	if (cmdArgs != 3):
		print("You just need to provide a host name and port number. You provided too much or too litte. That's not very sweet :( please try again.")
		sys.exit(-1)
	try:
		host = sys.argv[1]
		port = sys.argv[2]
	except IndexError:
		print('You need to provide a host name and port number! Please try again :(')
		sys.exit()

	
	# create a socket
	try: 
		footSocks = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	except OSError as lostSockInLaundry:
		print('Socket creation error: %s' %(lostSockInLaundry))
		sys.exit()

	# get socket address then connect it to the server
	try:
		laundryBasket = socket.getaddrinfo(host, port, socket.AF_INET, socket.SOCK_STREAM)
		sockFoundInLaundry = laundryBasket[0]
		sockFamily, sockType, sockProto, sockcannoname, sockDrawer = sockFoundInLaundry
	except OSError as lostSockInLaundry:
		print('Connection failed. Maybe you entered the port number wrong? Please try again.')
		sys.exit()

	# connect socket to server
	try: #checks for socket connection errors
		footSocks.connect(sockDrawer)
	except OSError as lostMySockAgain:
		print('Socket to server connection error: %s' %(lostMySockAgain))
		sys.exit(-1)





	# huzzah. Now we can prompt the user to enter a nickname
	print('Please enter your nickname to be displayed in the chat room.')
	nickname = input()
	footSocks.sendall(sendingPromptMessage(nickname))


	# // recieve message from server indicating whether or not nickname is valid

	sockMsg = totallyReadingText(footSocks)
	print(sockMsg)
	while True:
		if sockMsg == '"READY"':
			#message = input()
			#footSocks.sendall(sendingPromptMessage(message))
			#msg = totallyReadingText(footSocks)
			#print(msg)
			clientChat(footSocks, nickname)
			break
		elif sockMsg == '"RETRY"':
			print("That nickname is already in use by another user. That sucks. Please enter a different one: ")
			nickname = input()
			footSocks.sendall(sendingPromptMessage(nickname))
			sockMsg = totallyReadingText(footSocks)
		
	

	# end of main
