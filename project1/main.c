

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct creature{
	int name;
	int room;
	int type;
};
struct room{
	int state[5];
	struct creature *creatures[10];
	int numOfCreatures;
};
void changeRoom();
void incrementScore();
void decrementScore();
struct room rooms[100];
struct creature creatures[100];
int numOfRooms = 0;
int numOfCreatures = 0;
int score = 40;
int currentRoom = 0;
int endGame = 0; 
void initializeWorld();
void getRoomData();
void help()
{
	printf("\nexit: ends the current game");
	printf("\neast,west,north,south: directions player can move if possible");
	printf("\nclean: cleans current room from dirty or half dirty");
	printf("\n#:clean: cleans a specific room by its number");
	printf("\nlook: gives information about current room");
}
void setNumOfRooms(int *num)
{
	numOfRooms = *num;
				
}
void changeRoomCleanliness(int r, int c)
{
	int numMoving = 0;
	int moving[10];
	int nc = 0;
	int rm = r;
	int clean = c;
	int state = rooms[rm].state[0];
	state = state + c;
	rooms[rm].state[0] = state;
	nc = rooms[rm].numOfCreatures;
	int i =0;
	while(i<nc)
	{
		struct creature c = *rooms[rm].creatures[i];
		int name =c.name;
		int type = c.type;
		if(type == 1)
		{
			if(clean<0)
			{
				printf("Animal %d licks your face", name);
				incrementScore();
				
			}
			else
			{
				printf("Animal %d bites your face", name);
				decrementScore();
				if(state>1)
				{
					if(rooms[rm].state[1]>=0)
					{	
						printf("Animal %d goes North", name);
						moving[numMoving]=i;
						changeRoom(name,1);
						++numMoving;

					}
					else if(rooms[rm].state[2]>=0)
					{
						printf("Animal %d goes South", name);
						moving[numMoving]=i;
						changeRoom(name,2);
						++numMoving;

					}	
					else if(rooms[rm].state[3]>=0)
					{
						printf("Animal %d goes East", name);
						moving[numMoving]=i;
						changeRoom(name,3);
						++numMoving;

					}	
					else if(rooms[rm].state[4]>=0)
					{
						printf("Animal %d goes West", name);
						moving[numMoving]=i;
						changeRoom(name,4);
						++numMoving;

					}
					else
					{
						printf("Animal %d combusts", name);
						++numMoving;

					}		
				}

			}
			
		}
		else if(type == 2)
		{	
			if(clean>0)
			{
				printf("Human %d pats your back", name);
				incrementScore();
				
			}
			else
			{
				printf("Human %d stabs your face", name);
				decrementScore();
				if(state>1)
				{
					if(rooms[rm].state[1]>=0)
					{	
						printf("Human %d goes North", name);
						moving[numMoving]=i;
						changeRoom(name,1);
						++numMoving;

					}
					else if(rooms[rm].state[2]>=0)
					{
						printf("Human %d goes South", name);
						moving[numMoving]=i;
						changeRoom(name,2);
						++numMoving;

					}	
					else if(rooms[rm].state[3]>=0)
					{
						printf("Human %d goes East", name);
						moving[numMoving]=i;
						changeRoom(name,3);
						++numMoving;

					}	
					else if(rooms[rm].state[4]>=0)
					{
						printf("Human %d goes West", name);
						moving[numMoving]=i;
						changeRoom(name,4);
						++numMoving;

					}
					else
					{
						printf("Human %d combusts", name);
						++numMoving;

					}		
				}
			}
			
		}
		
				
	++i;}

	
}
void changeRoom(int c, int r)
{
	int nc = 0;
	int lr = 0;
	if(c == 0)
	{
		currentRoom = r;
	}
	lr=creatures[c].room;
	creatures[c].room=r;
	nc = rooms[lr].numOfCreatures;
	rooms[lr].numOfCreatures = nc -1;
	nc = 0;
	nc = rooms[r].numOfCreatures;
	rooms[r].numOfCreatures = nc +1;

}
void setNumberOfCreatures(int *num)
{
	numOfCreatures = *num;		
}
void playGame()
{
	char move[20];
	while(strcmp(move,"exit")!=0)
	{
		scanf("%s",move);
		if(strcmp(move,"look") == 0)
		{
			getRoomData();
		}
		else if(strcmp(move,"help") == 0)
		{
			help();
		}
		else if(strcmp(move,"east") == 0)
		{
			int d = rooms[currentRoom].state[3];
			changeRoom(0,d);
		}
		else if(strcmp(move,"west") == 0)
		{
			int d = rooms[currentRoom].state[4];
			changeRoom(0,d);
		}
		else if(strcmp(move,"north") == 0)
		{
			int d = rooms[currentRoom].state[1];
			changeRoom(0,d);
		}
		else if(strcmp(move,"south") == 0)
		{
			int d = rooms[currentRoom].state[2];
			changeRoom(0,d);
		}
		else if(strcmp(move,"clean") == 0)
		{
			changeRoomCleanliness(currentRoom, 1);
		}
		else if(strcmp(move,"dirty") == 0)
		{
			changeRoomCleanliness(currentRoom, -1);
		}
		else if(strcmp(move,"exit") == 0){}
		else
		{	
			char n[4];
			char d[10];
			int s = 0;
			int t = 0;
			int c = 0;
			int l = strlen(move);
			while(move[s] != ':')
			{	
				n[s] = move[s];
				++s;
			}
			++s;
			while(s<l)
			{
				d[t] = move[s];
				++t;
				++s;
			}
			s = 0;
			s = atoi(n);
			if(strcmp(d,"clean") == 0)
			{
				c = 1;	
			}
			else
			{
				c = -1;
			}
			changeRoomCleanliness(s,c);
		}
		
	}	
}
void decrementScore()
{
	score = score - 1;
	printf("You lost cool points!\nYour new score is %d", score);
}
void incrementScore()
{
	score = score + 1;
	printf("You gained cool points!\nYour new score is %d", score);
}
void getRoomData()
{
	printf("You are in room %d.\n", currentRoom);
	int i = 1;
	int cleanliness = rooms[currentRoom].state[0];
	int neighbors = rooms[currentRoom].numOfCreatures;
	printf("\nNumOfCreatures %d",neighbors);
	if(cleanliness == 0)
	{
		printf("This room is clean");
	}
	else if(cleanliness == 1)
	{
		printf("This room is half clean.");
	}
	else
	{
		printf("This room is dirty");
	}
	while(i<5)
	{	int c = rooms[currentRoom].state[i];
		if(c != -1)
		{
			if(i==1)
			{
				printf("\nRoom to the North has %d occupants.", c);
			}
			else if(i==2)
			{
				printf("\nRoom to the South has %d occupants.", c);
			}
			else if(i==3)
			{
				printf("\nRoom to the East has %d occupants.", c);
			}
			else if(i==4)
			{
				printf("\nRoom to the West has %d occupants.", c);
			}
				
		}
		++i;

	}
	i = 0;
	while(i<neighbors)
	{	
		struct creature c = *rooms[currentRoom].creatures[i];
		int t = c.type;
		int n = c.name;		
		printf("\nThis room contains:\n");
		if(t==0)
		{
			printf("PC\n");
		}
		else if(t==1)
		{
			printf("animal %d\n",n);
		}	
		else
		{
			printf("human %d\n",n);
		} 
		++i;		
	}	
			
}
void initializeWorld()
{
	int r=0;
	scanf("%d",&r);
	setNumOfRooms(&r);
	r = 0;
	while(r<numOfRooms)
	{
		int state=0;
		int n = 0;
		int s = 0;
		int e = 0;
		int w = 0;
		//an array of pointers to room array
		scanf("%d%d%d%d%d", &state,&n,&s,&e,&w);
		rooms[r].state[0] = state;
		rooms[r].state[1] = n;
		rooms[r].state[2] = s;
		rooms[r].state[3] = e;
		rooms[r].state[4] = w;	
		++r;		
	}
	scanf("%d",&r);
	setNumberOfCreatures(&r);
	r=0;
	while(r<numOfCreatures)
	{
		int t = -1;
		int rm = -1;
		int nOc = 0;
		scanf("%d%d",&t,&rm);
		if(t==0)
		{
			currentRoom = rm;
		}
		creatures[r].name = r;
		creatures[r].type = t;
		creatures[r].room = rm;
		nOc = rooms[rm].numOfCreatures;
		rooms[rm].creatures[nOc]=&creatures[r];
		rooms[rm].numOfCreatures = nOc + 1;
		++r;	
	}	
	playGame();	
} 
int main()
{
	
	initializeWorld();

	return 0;
}
