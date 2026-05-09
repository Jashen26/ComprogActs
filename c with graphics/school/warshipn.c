#include<stdio.h>

int main()
{char CLASS_ID;

printf("Input Class ID (B) for Battleship (C) for Cruiser (D) for Destroyer (F) for Trigate: \n");
scanf("%c", &CLASS_ID);

switch(CLASS_ID){
    case 'B':
    case 'b':
    {printf("You have chosen the Battleship");
    break;
}

case 'C':
case 'c':
{printf("You have chosen the Cruiser");
break;}

case 'D':
case 'd':
{printf("You have chosen the Destroyer");
break;
}

case 'F':
case 'f':
{printf("You have chosen the Trigate");
break;
}

default: {printf("NOT A WARSHIP");}

}
return 0;
}