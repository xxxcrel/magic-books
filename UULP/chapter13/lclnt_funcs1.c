/****************************************************************************
 * lsrv_funcs1.c
 * functions for the license server
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <sys/errno.h>

#define SERVER_PORTNUM 2020 /* Our server's port number */
#define MSGLEN 128          /* Size of our datagrams */
#define TICKET_AVAIL 0      /* Slot is available for use */
#define MAXUSERS 3          /* Only 3 users for us */
#define oops(x)    \
    {              \
        perror(x); \
        exit(-1);  \
    }

/****************************************************************************
 * Important variables
 */
int ticket_array[MAXUSERS]; /* Our ticket array */
int sd = -1;                /* Our socket */
int num_tickets_out = 0;    /* Number of tickets outstanding */

char *do_hello();
char *do_goodbye();

/****************************************************************************
 * setup() - initialize license server
 */
setup()
{
    sd = make_dgram_server_socket(SERVER_PORTNUM);
    if (sd == -1)
        oops("make socket");
    free_all_tickets();
    return sd;
}
free_all_tickets()
{
    int i;

    for (i = 0; i < MAXUSERS; i++)
        ticket_array[i] = TICKET_AVAIL;
}

/****************************************************************************
 * shut_down() - close down license server
 */
shut_down()
{
    close(sd);
}

/****************************************************************************
 * handle_request(request, clientaddr, addrlen)
 *   branch on code in request
 */
handle_request(char *req, struct sockaddr_in *client, socklen_t addlen)
{
    char *response;
    int ret;

    /* act and compose a response */
    if (strncmp(req, "HELO", 4) == 0)
        response = do_hello(req);
    else if (strncmp(req, "GBYE", 4) == 0)
        response = do_goodbye(req);
    else
        response = "FAIL invalid request";

    /* send the response to the client */
    narrate("SAID:", response, client);
    ret = sendto(sd, response, strlen(response), 0,
                 (struct sockaddr *)client, addlen);
    if (ret == -1)
        perror("SERVER sendto failed");
}

/****************************************************************************
 * do_hello
 * Give out a ticket if any are available
 * IN  msg_p			message received from client
 * Results: ptr to response
 *    NOTE: return is in static buffer overwritten by each call
 */
char *do_hello(char *msg_p)
{
    int x;
    static char replybuf[MSGLEN];

    if (num_tickets_out >= MAXUSERS)
        return ("FAIL no tickets available");

    /* else find a free ticket and give it to client */

    for (x = 0; x < MAXUSERS && ticket_array[x] != TICKET_AVAIL; x++)
        ;

    /* A sanity check - should never happen */
    if (x == MAXUSERS)
    {
        narrate("database corrupt", "", NULL);
        return ("FAIL database corrupt");
    }

    /* Found a free ticket.  Record "name" of user (pid) in array.
	 * 	generate ticket of form: pid.slot
	 */
    ticket_array[x] = atoi(msg_p + 5); /* get pid in msg */
    sprintf(replybuf, "TICK %d.%d", ticket_array[x], x);
    num_tickets_out++;
    return (replybuf);
} /* do_hello */

/****************************************************************************
 * do_goodbye
 * Take back ticket client is returning
 * IN  msg_p			message received from client
 * Results: ptr to response
 */
char *do_goodbye(char *msg_p)
{
    int pid, slot; /* components of ticket	*/

    /* The user's giving us back a ticket.  First we need to get
 	 * the ticket out of the message, which looks like:
	 *
	 * 	GBYE pid.slot
	 */
    if ((sscanf((msg_p + 5), "%d.%d", &pid, &slot) != 2) ||
        (ticket_array[slot] != pid))
    {
        narrate("Bogus ticket", msg_p + 5, NULL);
        return ("FAIL invalid ticket");
    }

    /* The ticket is valid.  Release it. */
    ticket_array[slot] = TICKET_AVAIL;
    num_tickets_out--;

    /* Return response */
    return ("THNX See ya!");
} /* do_goodbye */

/****************************************************************************
 * narrate() - chatty news for debugging and logging purposes
 */
narrate(char *msg1, char *msg2, struct sockaddr_in *clientp)
{
    fprintf(stderr, "\t\tSERVER: %s %s ", msg1, msg2);
    if (clientp)
        fprintf(stderr, "(%s:%d)", inet_ntoa(clientp->sin_addr),
                ntohs(clientp->sin_port));
    putc('\n', stderr);
}