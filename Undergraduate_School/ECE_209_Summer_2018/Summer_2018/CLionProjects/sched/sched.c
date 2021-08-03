/* ECE 209 - Summer 2018
 * Program 3 - TV Guide
 * sched.c
 * Andrew Albright
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sched.h"

int checkTimeConstraints(ShowList p, struct showTime start, struct showTime end);

/* definition of structs: channel and show */
struct channel{
    int chanNum;
    char chanName[21];
    ShowList showHead[7];
};

struct show{
    char day[4];
    char showName[21];
    struct channel * Channel;
    struct showTime start;
    struct showTime end;
};

/* creating the head of a channel/show list */
ChannelList chanHead = NULL;

/* creating a struct day to link the channels host pointers to each show */
const ChannelList day[7] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};

/* array of list of channels for every day of the week */
//struct channelNode day[7];

/* developed functions */

/* creates a new Channel and adds it to the system */
Channel addChannel(int num, const char* name){
    ChannelList newChannel, before, p;
    before = chanHead; p = chanHead;

    /* create new 'channelNode' struct and 'channel' struct */
    newChannel = (ChannelList)malloc(sizeof(struct channelNode));
    newChannel->c = (Channel)malloc(sizeof(struct channel));
    newChannel->next = NULL;

    /* give values to the channel struct */
    newChannel->c->chanNum = num;
    strcpy(newChannel->c->chanName, name);
    int i;
    for(i = 0; i < 7; i++) {
        newChannel->c->showHead[i] = NULL;
    }

    /* check if channel already exists */
    while(p){
        if(p->c->chanNum == num) return NULL;
        p = p->next;
    }
    p = chanHead;

    /* check if num is a negative number */
    if(num < 0) return NULL;

    /* if list is empty */
    if(chanHead == NULL) {
        chanHead = newChannel;
        newChannel->next = NULL;
    }
    /* if list has one or more channels already */
    else{
        /* if list has one channel in it */
        if(p->next == NULL){
            if(p->c->chanNum < num){
                p->next = newChannel;
                newChannel->next = NULL;
            }
            else{
                chanHead = newChannel;
                newChannel->next = p;
            }
        }
        /* if list has more than one channel in it */
        else{
            while(p){
                if(p->c->chanNum > num) break;
                else{
                    p = p->next;
                    if(p != chanHead->next) before = before->next;
                }
            }
            /* if never moved from the beginning (prepend) */
            if(p == chanHead){
                chanHead = newChannel;
                newChannel->next = p;
            }
            /* if reached end of list (append) */
            else if(p == NULL){
                before->next = newChannel;
                newChannel->next = NULL;
            }
            /* must be somewhere in the middle */
            else {
                before->next = newChannel;
                newChannel->next = p;
            }
        }

    }

    return newChannel->c;
}

/* Returns the number (integer) associated with c. */
int channelNum(Channel c){
    return c->chanNum;
}

/* Returns the name (string) associated with c.  */
const char* channelName(Channel c) {  /* pointer to name string */
    return c->chanName;
}

/* Returns Channel on which s appears.  */
Channel showChannel(Show s){
    return s->Channel;
}

/* Returns name (string) of s.  */
const char* showName(Show s) {  /* pointer to name string */
    return s->showName;
}

/* Returns day (string) when s is scheduled.  */
const char* showDay(Show s) {   /* pointer to day string */
    return s->day;
}

/* Returns starting time (struct showTime) of s. */
struct showTime showStart(Show s){
    return s->start;
}

/* Returns ending time (struct showTime) of s. */
struct showTime showEnd(Show s){
    return s->end;
}

/* Returns a list of all channels in the schedule, in increasing order by number.  */
ChannelList allChannels(){
    ChannelList p, p2, newHead = NULL;
    p = chanHead; p2 = newHead;

    while(p){
        ChannelList newNode;
        newNode = (ChannelList)malloc(sizeof(struct channelNode));

        /* if the list is just starting */
        if(newHead == NULL){
            newHead = newNode;
            newNode->c = p->c;
            newNode->next = NULL;
            p2 = newHead;
        }

            /* if the list has at least one node */
        else{
            p2->next = newNode;
            newNode->c = p->c;
            newNode->next = NULL;
            p2 = p2->next;
        }
        p = p->next;
    }
    return newHead;
}

/* Returns a pointer to the channel with the specified number. If no such channel, returns NULL. */
Channel findChannel(int num) {
    ChannelList p, returnChannel;
    p = chanHead;

    returnChannel = (ChannelList)malloc(sizeof(struct channelNode));
    returnChannel->c = NULL;
    returnChannel->next = NULL;

    while(p){
        if(p->c->chanNum == num){
            returnChannel->c = p->c;
        }
        p = p->next;
    }
    return returnChannel->c;
}

/* dummy functions */

Show addShow(Channel c, const char* name, const char* day, struct showTime start, struct showTime end){
    /* find what day the show is on */
    int DAY;
    if(!strcmp(MON, day)) DAY = 0;
    else if(!strcmp(TUE, day)) DAY = 1;
    else if(!strcmp(WED, day)) DAY = 2;
    else if(!strcmp(THU, day)) DAY = 3;
    else if(!strcmp(FRI, day)) DAY = 4;
    else if(!strcmp(SAT, day)) DAY = 5;
    else DAY = 6;

    /* find the channel the show goes on; set pointer 'channel' to that */
    ChannelList channel = chanHead;
    while(channel){
        if(channel->c == c) break;
        channel = channel->next;
    }
    /* channel doesn't exist */
    if(channel == NULL) return NULL;

    /* channel exists */
    else {
        ShowList newShow, before, p, after;
        /* set pointers to the head of the show list for the day the show is on */
        p = channel->c->showHead[DAY]; before = channel->c->showHead[DAY]; after = NULL;

        /* check for time constraints; DEFINE FARTHER POSSIBLY; reset the pointer 'p' */
        if(checkTimeConstraints(p, start, end)) return NULL;

        /* reset pointer 'p' */
        p = channel->c->showHead[DAY];

        /* no time constraints exist; create new 'showNode' struct and 'show' struct */
        newShow = (ShowList) malloc(sizeof(struct showNode));
        newShow->s = (Show) malloc(sizeof(struct show));
        newShow->next = NULL;

        /* assign values to newly created show */
        newShow->s->start = start;
        newShow->s->end = end;
        newShow->s->Channel = c;
        strcpy(newShow->s->day, day);
        strcpy(newShow->s->showName, name);

        /* if no shows have been programmed for the day and time */
        if(channel->c->showHead[DAY] == NULL){
            channel->c->showHead[DAY] = newShow;
            newShow->next = NULL;
        }

        /* one or more show(s) have been programmed for the day */
        else{
            /* if list has only one show */
            if(p->next == NULL){
                /* if the show is before the other show */
                if(newShow->s->end.hour < p->s->start.hour) {
                    channel->c->showHead[DAY] = newShow;
                    newShow->next = p;
                }
                /* could be before or after */
                else if(newShow->s->end.hour == p->s->start.hour){
                    /* before */
                    if(newShow->s->end.min < p->s->start.min) {
                        channel->c->showHead[DAY] = newShow;
                        newShow->next = p;
                    }
                    /* after */
                    else{
                        p->next = newShow;
                        newShow->next = NULL;
                    }
                }
                /* if the show is after the other show */
                else{
                  p->next = newShow;
                  newShow->next = NULL;
                }
            }
            /* the list has more than one show in it */
            else{

                int i = 0;
                while(p){
                    /* if the shows ever fall in the same hour */
                    if(p->s->start.hour == newShow->s->start.hour){ i = 0; break;}
                    if(p->s->start.hour == newShow->s->end.hour){i = 0; break;}
                    if(p->s->end.hour == newShow->s->start.hour){i = 0; break;}
                    if(p->s->end.hour == newShow->s->end.hour){i = 0; break;}

                    /* find the first place where the start hour is greater than new end hour */
                    if(p->s->start.hour > newShow->s->end.hour){i = 1; break;}

                    p = p->next;
                    if(p != channel->c->showHead[DAY]->next) before = before->next;
                }
                /* show is to be inserted at the beginning of list */
                if(p == channel->c->showHead[DAY]){
                    channel->c->showHead[DAY] = newShow;
                    newShow->next = p;
                }
                /* show is to be inserted at the end of the list (prepend) */
                else if(p == NULL){
                    before->next = newShow;
                    newShow->next = NULL;
                }
                /* somewhere in the middle */
                else{
                    if(i == 0){
                        /* if both shows start in the same hour */
                        if(p->s->start.hour == newShow->s->start.hour){
                            /* if the pointed show starts first */
                            if(p->s->start.min < newShow->s->start.min){
                                after = p->next;
                                p->next = newShow;
                                newShow->next = after;
                            }
                            /* if the new show starts first */
                            else{
                                before->next = newShow;
                                newShow->next = p;
                            }
                        }
                        /* if the new show ends in the same hour of the pointed shows start */
                        else if(p->s->start.hour == newShow->s->end.hour){
                            /* new show starts first */
                            before->next = newShow;
                            newShow->next = p;
                        }
                        /* if the new show starts in the same hour of the pointed shows end */
                        else if(p->s->end.hour == newShow->s->start.hour){
                            /* pointed show starts first */
                            after = p->next;
                            p->next = newShow;
                            newShow->next = after;
                        }
                        /* if the both shows end in the same hour */
                        else if(p->s->end.hour == newShow->s->end.hour){
                            /* if the pointed show ends first */
                            if(p->s->end.min < newShow->s->end.min){
                                after = p->next;
                                p->next = newShow;
                                newShow->next = after;
                            }
                            /* if the new show ends first */
                            else{
                                before->next = newShow;
                                newShow->next = p;
                            }

                        }

                    }
                    /* new show starts before pointed show */
                    else if(i == 1){
                        before->next = newShow;
                        newShow->next = p;
                    }
                }







            }
        }
    }
    return channel->c->showHead[DAY]->s;
}

ShowList findShows(Channel c, const char* name, const char *day, struct showTime* time){
    return NULL;
}

int checkTimeConstraints(ShowList p, struct showTime start, struct showTime end){
    int chk = 0;

    while(p) {
        /* if new show starts within the time of pointed show */
        if (start.hour >= p->s->start.hour && start.hour <= p->s->end.hour && start.min < p->s->end.min) {
            return NULL;
        }

        /* if new show ends within the hours of pointed show */
        if(end.hour >= p->s->start.hour && end.hour <= p->s->end.hour && end.min > p->s->start.min){
            /* if new show ends after pointed show starts */
            if(end.min > p->s->start.min) return NULL;
        }

        /* if the start of new is before the pointed, and the end time is after */
        if(start.hour < p->s->start.hour && end.hour > p->s->start.hour) return NULL;
        if(start.hour == p->s->start.hour && start.min < p->s->start.min && end.min > p->s->end.min)
            return NULL;

        p = p->next;
    }

    return chk;
}
/* NOTES:
 *
 * typedef struct channel * Channel;
 * typedef struct show * Show;
 *
 * typedef struct channelNode * ChannelList;
 * typedef struct showNode * ShowList;
 *
 *
 *
 * left program at: placing a show in the middle of the list in order by time
 */
