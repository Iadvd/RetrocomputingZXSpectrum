//tcpipsrv_basic.c

// This file will create a server side TCP listener on port 8081
// for a ZX Spectrum computer. The compiler will create a .tap file
// that can be run in the Fuse Spectrum Emulator with the Spectranet peripheral emulation
// it will also run in a real ZX Spectrum with a real Spectranet peripheral
// https://sourceforge.net/p/fuse-emulator/wiki/Spectranet%20Emulation/
// http://spectrum.alioth.net/doc/index.php/Main_Page

// Credits for the original basic example code to: 
// http://spectrum.alioth.net/doc/index.php/Software#Programmer.27s_Guide
// Please feel free to reuse this code and modify it as you need

// Remark: libsocket is has been recompiled to work with the newest version of z88dk 
// for this reason, we have included a compatible copy at our github place
// it will compile and create a ZX emulation .tap file that can be run in Fuse or a real ZX Spectrum
// if converted into a sound file (for the EAR channel) or loaded through other nowadays retrocomputing peripherals

// For other retrocomputing projects that are using older z88dk versions we are using the original libsocket 
// compatible library

/* A demonstration of the use of poll to avoid blocking. This allows
 * multiple sockets to be read and accepted, and interleaved with keypresses.
 *
 * Compile with:
zcc +zx -vn -O2 -create-app -o tcpipsrv_basic.bin tcpipsrv_basic.c -lndos -llibsocket */


#include <stdio.h>
#include <input.h>              /* for in_Inkey() */
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sockpoll.h>
#include <conio.h>
#include <time.h>

main()
{
        int sockfd, connfd, polled, rc;
        struct sockaddr_in my_addr;
        char txdata[40];
        char rxdata[128];
        struct pollfd p;        /* the poll information structure */

		int joystick_clear_counterL = 0;
		int joystick_clear_counterR = 0;
		int joystick_clear_counterU = 0;
		int joystick_clear_counterD = 0;
		int joystick_clear_counterB1 = 0;
		int joystick_clear_counterB2 = 0;
		int joystick_clear_counterB3 = 0;
		int sent_ack_first_time = 0;
				
		const int PROTOCOL_MSGS_X = 0;
		const int PROTOCOL_MSGS_Y = 1;
		const int SENSOR_MSGS_X = 0;
		const int SENSOR_MSGS_Y = 5;
		const int JOYSTICK_MSGS_X = 0;
		const int JOYSTICK_MSGS_Y = 53;
		
		char *retV;
											
		/* 0x0C clears the screen in the z88dk default console driver */
        putchar(0x0C);
		zx_border(INK_WHITE);
		
		textcolor(BLACK);
		textbackground(WHITE);
		
		gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y-1);
		printf("TCP/IP NOTIFICATIONS:");
		
		gotoxy(JOYSTICK_MSGS_X,JOYSTICK_MSGS_Y-2);
		printf("VIRTUAL JOYSTICK RECEIVED COMMANDS:");
		
		textcolor(WHITE);
		textbackground(BLUE);
		
		gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
		printf("                                                      ");
		gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
		printf("STARTING BEACON TEST");
		
		while(1)
		{
				/* Create the socket */
				/* The first argument, AF_INET is the family. The Spectranet only
				   supports AF_INET at present. SOCK_STREAM in this context is
				   for a TCP connection. */
				sockfd=socket(AF_INET, SOCK_STREAM, 0);
				if(sockfd < 0)
				{
						textcolor(BLACK);
						textbackground(WHITE);
						gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
						printf("                                                      ");
						gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
						printf("Could not open the socket - rc=%d", sockfd);
						return;
				}

				/* Now set up the sockaddr_in structure. */
				/* Zero it out so that any fields we don't set are set to
				   NULL (the structure also contains the local address to bind to). 
				   We will listne to port 8081. */
				memset(&my_addr, 0, sizeof(my_addr));   /* zero out all fields */
				my_addr.sin_family=AF_INET;
				my_addr.sin_port=htons(8081);           /* Port 8081 */

				if(bind(sockfd, &my_addr, sizeof(my_addr)) < 0)
				{
						gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
						printf("                                                      ");
						gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
						printf("Bind failed.");
						sockclose(sockfd);
						return;
				}

				/* The socket should now listen. The Spectranet hardware in
				   its present form doesn't support changing the backlog, but
				   the second argument to listen should still be a sensible value */
				if(listen(sockfd, 1) < 0)
				{
						gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
						printf("                                                      ");
						gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
						printf("listen failed.");
						sockclose(sockfd);
						return;
				}

				gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
				printf("                                                      ");
				gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
				printf("Listening on port 8081.");
				sent_ack_first_time=0;
				
				/* Now wait for things to happen. Contrast this with the server
				   code example in tutorial 2. Note that instead of calling accept()
				   we start a loop, and use the pollall() function to poll all open
				   sockets. When pollall() finds some data ready, it returns
				   status telling us why the socket was ready, so we can act
				   appropriately */
				while(1)
				{
						if(joystick_clear_counterL == 0)
						{
							gotoxy(JOYSTICK_MSGS_X,JOYSTICK_MSGS_Y+1);
							printf("      ");
						}
						else{
							joystick_clear_counterL = joystick_clear_counterL-1;
						}
						
						if(joystick_clear_counterR == 0)
						{
							gotoxy(JOYSTICK_MSGS_X+12,JOYSTICK_MSGS_Y+1);
							printf("      ");
						}
						else{
							joystick_clear_counterR = joystick_clear_counterR-1;
						}
						
						if(joystick_clear_counterU == 0)
						{
							gotoxy(JOYSTICK_MSGS_X+6,JOYSTICK_MSGS_Y);
							printf("      ");
						}
						else{
							joystick_clear_counterU = joystick_clear_counterU-1;
						}
						
						if(joystick_clear_counterD == 0)
						{
							gotoxy(JOYSTICK_MSGS_X+6,JOYSTICK_MSGS_Y+2);
							printf("      ");
						}
						else{
							joystick_clear_counterD = joystick_clear_counterD-1;
						}
						
						if(joystick_clear_counterB1 == 0)
						{
							gotoxy(JOYSTICK_MSGS_X+24,JOYSTICK_MSGS_Y+1);
							printf("       ");
						}
						else{
							joystick_clear_counterB1 = joystick_clear_counterB1-1;
						}
						
						if(joystick_clear_counterB2 == 0)
						{
							gotoxy(JOYSTICK_MSGS_X+36,JOYSTICK_MSGS_Y+1);
							printf("       ");
						}
						else{
							joystick_clear_counterB2 = joystick_clear_counterB2-1;
						}
						
						if(joystick_clear_counterB3 == 0)
						{
							//gotoxy(JOYSTICK_MSGS_X+6,JOYSTICK_MSGS_Y+2);
							//printf("       ");
						}
						else{
							joystick_clear_counterB3 = joystick_clear_counterB3-1;
						}
						
						/* This shows the keyboard being multiplexed with sockets */
						if(in_Inkey() == 'x'){
							/* Close the listening socket and exit. */
							sockclose(sockfd);
							printk("Finished.\n");
							exit(0);
						}
								

						/* pollall() fills a pollfd struct when something happens.
						   It returns the socket descriptor on which that something
						   happened */
						polled=pollall(&p);

						/* Was the socket descriptor the listening socket? */
						if(polled == sockfd)
						{
								/* Yes. So accept the incoming connection. */
								gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
								printf("                                                      ");
								gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
								printf("Accepting a new connection...");
								connfd=accept(sockfd, NULL, NULL);
						}
						/* if any other socket descriptor returned status, then
						   something happened on a communication socket */
						else if(polled > 0)
						{
								/* Did the other end hang up on us? */
								if(p.revents & POLLHUP)
								{
										gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
										printf("                                                      ");
										gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
										printf("Remote host disconnected");
										
										/* ...so close our end too and free the fd */
										sockclose(polled);
										
										/* Close the listening socket and exit while. */
										sockclose(sockfd);
										break;
								}
								/* No, the other end didn't hang up */
								else
								{
										/* Some data is ready to collect */
										rc=recv(polled, rxdata, sizeof(rxdata)-1, 0);
										if(rc < 0)
										{
												gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
												printf("                                                      ");
												gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
												printf("recv failed!");
												sockclose(polled);
												
												/* Close the listening socket and exit while. */
												sockclose(sockfd);
												break;
										}
						
										/* Ensure there's a null on the end */
										*(rxdata+rc)=0;
										
										retV=strstr(rxdata, "UP");
										if(retV != NULL) {
											gotoxy(JOYSTICK_MSGS_X+6,JOYSTICK_MSGS_Y);
											textcolor(WHITE);
											textbackground(RED);
											printf("UP    ");
											joystick_clear_counterU = 20;
											textcolor(WHITE);
											textbackground(BLUE);
										}
										
										retV=strstr(rxdata, "DOWN");
										if(retV != NULL) {
											gotoxy(JOYSTICK_MSGS_X+6,JOYSTICK_MSGS_Y+2);
											textcolor(WHITE);
											textbackground(RED);
											printf("DOWN  ");
											joystick_clear_counterD = 20;
											textcolor(WHITE);
											textbackground(BLUE);
										}
										
										retV=strstr(rxdata, "LEFT");
										if(retV != NULL) {
											gotoxy(JOYSTICK_MSGS_X,JOYSTICK_MSGS_Y+1);
											textcolor(WHITE);
											textbackground(RED);
											printf("LEFT  ");
											joystick_clear_counterL = 20;
											textcolor(WHITE);
											textbackground(BLUE);
										}
										
										retV=strstr(rxdata, "RIGHT");
										if(retV != NULL) {
											gotoxy(JOYSTICK_MSGS_X+12,JOYSTICK_MSGS_Y+1);
											textcolor(WHITE);
											textbackground(RED);
											printf("RIGHT ");
											joystick_clear_counterR = 20;
											textcolor(WHITE);
											textbackground(BLUE);
										}
										
										retV=strstr(rxdata, "BUTTON1");
										if(retV != NULL) {
											gotoxy(JOYSTICK_MSGS_X+24,JOYSTICK_MSGS_Y+1);
											textcolor(WHITE);
											textbackground(RED);
											printf("BUTTON1");
											textcolor(WHITE);
											textbackground(BLUE);
											joystick_clear_counterB1 = 20;
										}
										
										retV=strstr(rxdata, "BUTTON2");
										if(retV != NULL) {
											gotoxy(JOYSTICK_MSGS_X+36,JOYSTICK_MSGS_Y+1);
											textcolor(WHITE);
											textbackground(RED);
											printf("BUTTON2");
											textcolor(WHITE);
											textbackground(BLUE);
											joystick_clear_counterB2 = 20;
										}
										
										retV=strstr(rxdata, "BUTTON3");
										if(retV != NULL) {
											gotoxy(JOYSTICK_MSGS_X,JOYSTICK_MSGS_Y);
											textcolor(WHITE);
											textbackground(RED);
											printf("BUTTON3");
											textcolor(WHITE);
											textbackground(BLUE);
											joystick_clear_counterB3 = 20;
										}
										
										/* Send ID to client. This will verify that I am the correct IP */
										if (sent_ack_first_time==0){
											gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
											printf("                                                      ");
											gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
											printf("SENDING WELCOME ACK TO TCP/IP JOYSTICK");
											
											sent_ack_first_time=1;
											
											sprintf(txdata, "TCPIPJOYSTICKSPECTRUM\r\n", rc);
											rc=send(polled, txdata, strlen(txdata), 0);
											if(rc < 0)
											{
												sent_ack_first_time=0;
												gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
												printf("                                                      ");
												gotoxy(PROTOCOL_MSGS_X,PROTOCOL_MSGS_Y);
												printf("WELCOME ACK TI TCP/IP JOYSTICK SEND FAILED!");
												sockclose(polled);
												
												/* Close the listening socket and exit while. */
												sockclose(sockfd);
												break;
										
											}	
											
										}
										
								}
						}
				}                       

				/* Close the listening socket and exit. */
				//sockclose(sockfd);
				//printk("Finished.\n");
		}
		
}

