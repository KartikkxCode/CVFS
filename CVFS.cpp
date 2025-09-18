///////////////////////////////////////////////////////////////////////////////////////
//
//      Header files inclusion
//
//////////////////////////////////////////////////////////////////////////////////////


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>

#include<iostream>
using namespace std;


///////////////////////////////////////////////////////////////////////////////////////
//
//      User Defined Micros
//
//////////////////////////////////////////////////////////////////////////////////////


# define MAXFILESIZE 100

# define MAXINODE 5

# define READ 1
# define WRITE 2
# define EXECUTE 4

# define REGULARFILE 1
# define SPECIALFILE 2

# define START 0
# define CURRENT 1
# define END 2

# define EXECUTE_SUCCESS 0


///////////////////////////////////////////////////////////////////////////////////////
//
//      User Defined Micros for Error Handling
//
//////////////////////////////////////////////////////////////////////////////////////


#define ERR_INVALID_PARAMETER -1
#define ERR_NO_INODES -2
#define ERR_FILE_ALREADY_EXIST -3
#define ERR_FILE_NOT_FOUND -4
#define ERR_PERMISSION_DENIED -5
#define ERR_INVALID_FD -6
#define ERR_WRITE_EXCEED -7
#define ERR_FILE_BUSY -8

///////////////////////////////////////////////////////////////////////////////////////
//
//      Structure Name : BootBlock
//      Descreption    : Holds Information to the Operating System
//
//////////////////////////////////////////////////////////////////////////////////////


struct BootBlock
{
    char Information[100];
};


///////////////////////////////////////////////////////////////////////////////////////
//
//      Structure Name : SuperBlock
//      Descreption    : Holds Information to the File System
//
//////////////////////////////////////////////////////////////////////////////////////


struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};


///////////////////////////////////////////////////////////////////////////////////////
//
//      Structure Name : Inode
//      Descreption    : Holds Information to the File 
//
//////////////////////////////////////////////////////////////////////////////////////


typedef struct Inode
{
    char FileName[50];
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int FileType;
    int ReferenceCount;
    int LinkCount;
    int Permission;
    char *Buffer;
    struct Inode *next;
}INODE, *PINODE, **PPINODE;


///////////////////////////////////////////////////////////////////////////////////////
//
//      Structure Name : FileTable
//      Descreption    : Holds Information about the opened file 
//
//////////////////////////////////////////////////////////////////////////////////////


typedef struct FileTable
{
    int Offset;
    int Count;
    int Mode;
    PINODE ptrinode;
}FILETABLE, *PFILETABLE;


///////////////////////////////////////////////////////////////////////////////////////
//
//      Structure Name : UAREA
//      Descreption    : Holds Information about process
//
//////////////////////////////////////////////////////////////////////////////////////


struct UAREA
{
    char ProcessName[50];
    PFILETABLE UFDT[MAXINODE];
};


///////////////////////////////////////////////////////////////////////////////////////
//
//      Globel Veriable or Object used
//
//////////////////////////////////////////////////////////////////////////////////////

BootBlock bootobj;
SuperBlock superobj;
PINODE head = NULL;
UAREA uareaobj;


///////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name : InitialiseUAREA
//      Descreption   : It is used to initilise the UARE
//      Auther        : Kartik Anilrao Dahale
//      Date          : 10/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////


void InitialiseUAREA()
{
    strcpy(uareaobj.ProcessName,"myexe");

    int i = 0;

    while(i < MAXINODE)
    {
        uareaobj.UFDT[i] = NULL;
        i++;
    }
    cout<<"Marvellous CVFS : UAREA Initilise Successfully\n";
}


///////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name : InitialiseSuperBlock
//      Descreption   : It is used to initilise the contents of super block
//      Auther        : Kartik Anilrao Dahale
//      Date          : 10/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////


void InitialiseSuperBlock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    cout<<"Marvellous CVFS : SuperBlock Initilise Successfully\n";
}


///////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name : CreateDILB
//      Descreption   : It is used to Create linked list of inode
//      Auther        : Kartik Anilrao Dahale
//      Date          : 10/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////


void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = NULL;

    while(i <= MAXINODE)
    {
        newn = new INODE;
        newn->InodeNumber = i;
        newn->FileSize = 0;
        newn->ActualFileSize = 0;
        newn->Permission = 0;
        newn->Buffer = NULL;
        newn->next = NULL;

        if(temp == NULL)
        {
            head = newn;
            temp = head;
        }
        else
        {
            temp -> next = newn;
            temp = temp -> next;
        }

        i++;
    } 
    cout<<"Marvellous CVFS : DILB Created Successfully\n";
}


///////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name : StartAuxilaryDataInitialisation
//      Descreption   : It is used to initilise the Auxilary data
//      Auther        : Kartik Anilrao Dahale
//      Date          : 10/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////


void StartAuxilaryDataInitialisation()
{
    strcpy(bootobj.Information , "Boot Process of Operating System is Done\n");

    cout<<bootobj.Information<<"\n";

    InitialiseSuperBlock();

    CreateDILB();

    InitialiseUAREA();

    cout<<"Marvellous CVFS : Auxilary Data Initilise Successfully\n";
}


///////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name : DisplayHelp
//      Descreption   : It is used to display the information about Command
//      Auther        : Kartik Anilrao Dahale
//      Date          : 11/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////


void DisplayHelp()
{
    printf("-------------------------------------------------------------------------------\n");
    printf("----------------------Command Manual of Marvellous CVFS------------------------\n");
    printf("-------------------------------------------------------------------------------\n");

    printf("exit : It is used to terminate shell of Marvellous CVFS\n");
    printf("clear : It is use clear the console of Marvellous CVSF\n");
    printf("creat : Create a new regular file\n");
    printf("open : Open an existing file\n");
    printf("close : Close an opened file\n");
    printf("read : Read data from a file\n");
    printf("write : Write data to a file\n");
    printf("lseek : Change the offset in a file\n");
    printf("rm : Remove a file\n");
    printf("ls : List all files\n");
    printf("stat : Display file system status\n");
    printf("man : Display manual page for a command\n");

    printf("-------------------------------------------------------------------------------\n");
}


///////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name : ManPage
//      Descreption   : It is used to display the Manual page of the command
//      Input         : It accepts the Command Name
//      Output        : Display the Manual details of the command
//      Auther        : Kartik Anilrao Dahale
//      Date          : 11/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////


void ManPage(
            char *name
        )
        
{
    if(strcmp(name,"creat") == 0)
    {
        printf("Description : This command is use to create new regular file on your file system \n");

        printf("Usage : creat File_name Permissions\n");
        printf("File_name : the name of file that you want to create\n");
        printf("Permissions : \n1 : Read \n2 : Write \n3 : Read + Write\n");
    }
    else if(strcmp(name,"open") == 0)
    {
        printf("Description : Open an existing regular file\n");

        printf("Usage : open File_name Mode\n");
        printf("File_name : the name of file to open\n");
        printf("Mode : \n1 : Read \n2 : Write \n3 : Read + Write\n");
    }
    else if(strcmp(name,"close") == 0)
    {
        printf("Description : Close an opened file\n");

        printf("Usage : close FD\n");
        printf("FD : File descriptor of the file to close\n");
    }
    else if(strcmp(name,"read") == 0)
    {
        printf("Description : Read data from a file\n");

        printf("Usage : read FD Count\n");
        printf("FD : File descriptor\n");
        printf("Count : Number of bytes to read\n");
    }
    else if(strcmp(name,"write") == 0)
    {
        printf("Description : Write data to a file\n");

        printf("Usage : write FD Data\n");
        printf("FD : File descriptor\n");
        printf("Data : Data to write (can have spaces)\n");
    }
    else if(strcmp(name,"lseek") == 0)
    {
        printf("Description : Change the file offset\n");

        printf("Usage : lseek FD Offset Whence\n");
        printf("FD : File descriptor\n");
        printf("Offset : Offset value\n");
        printf("Whence : 0 - Start, 1 - Current, 2 - End\n");
    }
    else if(strcmp(name,"rm") == 0)
    {
        printf("Description : Remove a file\n");

        printf("Usage : rm File_name\n");
    }
    else if(strcmp(name,"ls") == 0)
    {
        printf("Description : List all files\n");

        printf("Usage : ls\n");
    }
    else if(strcmp(name,"stat") == 0)
    {
        printf("Description : Display file system status\n");

        printf("Usage : stat\n");
    }
    else if(strcmp(name,"exit") == 0)
    {
        printf("Description : The command is use to Terminate the Marvellous CVFS \n");

        printf("Usage : exit\n");
    }
    else
    {
        printf("No manual entry for %s\n",name);
    }

}


///////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name : IsFileExists
//      Descreption   : It is used to check whether the given file name exists or not
//      Input         : It accepts the file name
//      Output        : returns the boolean value(true : it presents false: it not present)
//      Auther        : Kartik Anilrao Dahale
//      Date          : 11/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////


bool IsFileExists(
                    char *name //Name of file that you want to chech
                )
{
    PINODE temp = head;
    bool bFlag = false;

    while(temp != NULL)
    {
        if((strcmp(name,temp->FileName) == 0) && (temp -> FileType == REGULARFILE))
            {
                bFlag = true;
                break;
            }

            temp = temp -> next;
    }

    return bFlag;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name : CreateFile
//      Descreption   : It is used to creat new regular file
//      Input         : It accepts the file name and permission
//      Output        : returns the file discreapter
//      Auther        : Kartik Anilrao Dahale
//      Date          : 11/08/2025
//
///////////////////////////////////////////////////////////////////////////////////////


int CreateFile(
                char *name,             //Name of File
                int permission          //Permission to create the file
            )
{
    PINODE temp = head;
    int i = 0;
    //Filters

    //If File name is Missing
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    //If Permission is invalid
    if(permission < 1 || permission > 3)
    {
        return ERR_INVALID_PARAMETER;
    }
    //Check whether empty inode is there or not
    if(superobj.FreeInodes == 0)
    {
        return ERR_NO_INODES;
    }
    //check file is already exists or not
    if(IsFileExists(name) == true)
    {
        return ERR_FILE_ALREADY_EXIST;
    }

    //Loop to search free Inode

    while(temp != NULL)
    {
        if(temp->FileType == 0)
        {
            break;
        }
        temp = temp -> next;

    }

    //Inode not found
    if(temp == NULL)
    {
        printf("Inode not found\n");
        return -1;
    }

    //Search first non NULL value for UFDT
    for(i = 0; i < MAXINODE; i++)
    {
        if(uareaobj.UFDT[i] == NULL)
        {
            break;
        }
    }

    if(i == MAXINODE)
    {
        printf("Unable to create the file as MAX OPENED FILE LIMIT REACHED\n");
        return -1;
    }

    //Allocate memory for file table
    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FILETABLE));

    //Initialise element of file table
    uareaobj.UFDT[i] -> Offset = 0;
    uareaobj.UFDT[i] -> Count = 1;
    uareaobj.UFDT[i] -> Mode = permission;

    //Connect file table with IIT
    uareaobj.UFDT[i] -> ptrinode = temp;

    strcpy(uareaobj.UFDT[i] -> ptrinode -> FileName,name);
    uareaobj.UFDT[i] -> ptrinode -> FileSize = MAXFILESIZE;
    uareaobj.UFDT[i] -> ptrinode -> ActualFileSize = 0;
    uareaobj.UFDT[i] -> ptrinode -> FileType = REGULARFILE;
    uareaobj.UFDT[i] -> ptrinode -> ReferenceCount = 1;
    uareaobj.UFDT[i] -> ptrinode -> LinkCount = 1;
    uareaobj.UFDT[i] -> ptrinode -> Permission = permission;

    //Allocate memory for buffer

    uareaobj.UFDT[i] -> ptrinode -> Buffer = (char *)malloc(MAXFILESIZE);
    memset(uareaobj.UFDT[i] -> ptrinode -> Buffer, 0, MAXFILESIZE);

    superobj.FreeInodes--;

    return i;
    
}

///////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name : OpenFile
//      Description   : It is used to open an existing regular file
//      Input         : File name and mode
//      Output        : Returns FD or error
//
///////////////////////////////////////////////////////////////////////////////////////

int OpenFile(char *name, int mode)
{
    PINODE temp = head;
    int i = 0;

    if(name == NULL || mode < 1 || mode > 3)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(IsFileExists(name) == false)
    {
        return ERR_FILE_NOT_FOUND;
    }

    while(temp != NULL)
    {
        if(strcmp(temp->FileName, name) == 0 && temp->FileType == REGULARFILE)
        {
            break;
        }
        temp = temp->next;
    }

    if(temp == NULL)
    {
        return -1;
    }

    if((temp->Permission & mode) != mode)
    {
        return ERR_PERMISSION_DENIED;
    }

    for(i = 0; i < MAXINODE; i++)
    {
        if(uareaobj.UFDT[i] == NULL)
        {
            break;
        }
    }

    if(i == MAXINODE)
    {
        printf("Unable to open the file as MAX OPENED FILE LIMIT REACHED\n");
        return -1;
    }

    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FILETABLE));
    uareaobj.UFDT[i]->Offset = 0;
    uareaobj.UFDT[i]->Mode = mode;
    uareaobj.UFDT[i]->Count = 1;
    uareaobj.UFDT[i]->ptrinode = temp;
    temp->ReferenceCount++;

    return i;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name : CloseFile
//      Description   : Close an opened file by FD
//
///////////////////////////////////////////////////////////////////////////////////////

int CloseFile(int fd)
{
    if(fd < 0 || fd >= MAXINODE || uareaobj.UFDT[fd] == NULL)
    {
        return ERR_INVALID_FD;
    }

    PFILETABLE ft = uareaobj.UFDT[fd];
    ft->ptrinode->ReferenceCount--;
    free(ft);
    uareaobj.UFDT[fd] = NULL;

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name : WriteFile
//      Description   : Write data to file
//
///////////////////////////////////////////////////////////////////////////////////////

int WriteFile(int fd, char *data)
{
    if(fd < 0 || fd >= MAXINODE || uareaobj.UFDT[fd] == NULL)
    {
        return ERR_INVALID_FD;
    }
    if((uareaobj.UFDT[fd]->Mode & WRITE) == 0)
    {
        return ERR_PERMISSION_DENIED;
    }
    if(data == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    int len = strlen(data);
    if(len == 0)
    {
        return 0;
    }

    PFILETABLE ft = uareaobj.UFDT[fd];
    int available_space = ft->ptrinode->FileSize - ft->Offset;

    if(len > available_space)
    {
        return ERR_WRITE_EXCEED;
    }

    memcpy(ft->ptrinode->Buffer + ft->Offset, data, len);
    ft->Offset += len;
    if(ft->Offset > ft->ptrinode->ActualFileSize)
    {
        ft->ptrinode->ActualFileSize = ft->Offset;
    }

    return len;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name : ReadFile
//      Description   : Read data from file
//
///////////////////////////////////////////////////////////////////////////////////////

int ReadFile(int fd, char *buffer, int size)
{
    if(fd < 0 || fd >= MAXINODE || uareaobj.UFDT[fd] == NULL)
    {
        return ERR_INVALID_FD;
    }
    if((uareaobj.UFDT[fd]->Mode & READ) == 0)
    {
        return ERR_PERMISSION_DENIED;
    }
    if(buffer == NULL || size <= 0)
    {
        return ERR_INVALID_PARAMETER;
    }

    PFILETABLE ft = uareaobj.UFDT[fd];
    int available_data = ft->ptrinode->ActualFileSize - ft->Offset;

    if(available_data <= 0)
    {
        return 0;
    }

    int bytes_to_read = (size < available_data) ? size : available_data;
    memcpy(buffer, ft->ptrinode->Buffer + ft->Offset, bytes_to_read);
    ft->Offset += bytes_to_read;

    return bytes_to_read;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name : LseekFile
//      Description   : Change file offset
//
///////////////////////////////////////////////////////////////////////////////////////

int LseekFile(int fd, int size, int from)
{
    if(fd < 0 || fd >= MAXINODE || uareaobj.UFDT[fd] == NULL)
    {
        return ERR_INVALID_FD;
    }

    PFILETABLE ft = uareaobj.UFDT[fd];

    switch(from)
    {
        case START:
            ft->Offset = size;
            break;
        case CURRENT:
            ft->Offset += size;
            break;
        case END:
            ft->Offset = ft->ptrinode->ActualFileSize + size;
            break;
        default:
            return ERR_INVALID_PARAMETER;
    }

    if(ft->Offset < 0)
    {
        ft->Offset = 0;
    }
    if(ft->Offset > ft->ptrinode->FileSize)
    {
        ft->Offset = ft->ptrinode->FileSize;
    }

    return ft->Offset;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name : DeleteFile
//      Description   : Delete a file if not busy
//
///////////////////////////////////////////////////////////////////////////////////////

int DeleteFile(char *name)
{
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }
    if(IsFileExists(name) == false)
    {
        return ERR_FILE_NOT_FOUND;
    }

    PINODE temp = head;

    while(temp != NULL)
    {
        if(strcmp(name, temp->FileName) == 0 && temp->FileType == REGULARFILE)
        {
            break;
        }
        temp = temp->next;
    }

    if(temp->ReferenceCount > 0)
    {
        return ERR_FILE_BUSY;
    }

    free(temp->Buffer);
    temp->Buffer = NULL;
    temp->FileType = 0;
    temp->ActualFileSize = 0;
    temp->ReferenceCount = 0;
    temp->LinkCount = 0;
    temp->Permission = 0;
    strcpy(temp->FileName, "");

    superobj.FreeInodes++;

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name : ListFiles
//      Description   : List all files
//
///////////////////////////////////////////////////////////////////////////////////////

void ListFiles()
{
    PINODE temp = head;
    printf("Files in Marvellous CVFS:\n");
    printf("Inode\tName\tSize\tActualSize\tPerm\tRefCount\n");
    while(temp != NULL)
    {
        if(temp->FileType == REGULARFILE)
        {
            printf("%d\t%s\t%d\t%d\t\t%d\t%d\n",
                   temp->InodeNumber,
                   temp->FileName,
                   temp->FileSize,
                   temp->ActualFileSize,
                   temp->Permission,
                   temp->ReferenceCount);
        }
        temp = temp->next;
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name : DisplayStatus
//      Description   : Display FS status
//
///////////////////////////////////////////////////////////////////////////////////////

void DisplayStatus()
{
    printf("File System Status:\n");
    printf("Total Inodes: %d\n", superobj.TotalInodes);
    printf("Free Inodes: %d\n", superobj.FreeInodes);
    ListFiles();
}

///////////////////////////////////////////////////////////////////////////////////////
//
//      Function Name : Cleanup
//      Description   : Cleanup resources on exit
//
///////////////////////////////////////////////////////////////////////////////////////

void Cleanup()
{
    PINODE temp = head;
    while(temp != NULL)
    {
        if(temp->Buffer != NULL)
        {
            free(temp->Buffer);
        }
        PINODE curr = temp;
        temp = temp->next;
        delete curr;
    }
    head = NULL;

    for(int i = 0; i < MAXINODE; i++)
    {
        if(uareaobj.UFDT[i] != NULL)
        {
            free(uareaobj.UFDT[i]);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//
//      Entry Point Function
//
///////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char str[512] = {'\0'};
    char Command[5][80];
    char data[512];
    char read_buffer[ MAXFILESIZE + 1 ];
    int iCount = 0;
    int iRet = 0;

    StartAuxilaryDataInitialisation();

    cout<<"-------------------------------------------------------------------------------\n";
    cout<<"-------------------Marvellous CVFS Started Successfully------------------------\n";
    cout<<"-------------------------------------------------------------------------------\n";

    while(1)
    {
        printf("\nMarvellous CVFS > ");
        fflush(stdin);
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';

        iCount = sscanf(str, "%s %s %s %s", Command[0], Command[1], Command[2], Command[3]);

        if(iCount == 1)
        {
            if(strcmp(Command[0], "exit") == 0)
            {
                printf("Thank you for using Marvellous CVFS \n");
                printf("Deallocation all resources...\n");
                Cleanup();
                break;
            }
            else if(strcmp(Command[0], "help") == 0)
            {
                DisplayHelp();
            }
            else if(strcmp(Command[0], "clear") == 0)
            {
                system("clear");
            }
            else if(strcmp(Command[0], "ls") == 0)
            {
                ListFiles();
            }
            else if(strcmp(Command[0], "stat") == 0)
            {
                DisplayStatus();
            }
            else
            {
                printf("Command not found. Use 'help' for list of commands.\n");
            }
        }
        else if(iCount == 2)
        {
            if(strcmp(Command[0], "man") == 0)
            {
                ManPage(Command[1]);
            }
            else if(strcmp(Command[0], "rm") == 0)
            {
                iRet = DeleteFile(Command[1]);
                if(iRet == 0)
                {
                    printf("File deleted successfully.\n");
                }
                else if(iRet == ERR_FILE_NOT_FOUND)
                {
                    printf("Error: File not found.\n");
                }
                else if(iRet == ERR_FILE_BUSY)
                {
                    printf("Error: File is open, close it first.\n");
                }
                else
                {
                    printf("Error: Unable to delete file.\n");
                }
            }
            else if(strcmp(Command[0], "close") == 0)
            {
                iRet = CloseFile(atoi(Command[1]));
                if(iRet == 0)
                {
                    printf("File closed successfully.\n");
                }
                else if(iRet == ERR_INVALID_FD)
                {
                    printf("Error: Invalid FD.\n");
                }
            }
            else
            {
                printf("Command not found. Use 'help' for list of commands.\n");
            }
        }
        else if(iCount == 3)
        {
            if(strcmp(Command[0], "creat") == 0)
            {
                iRet = CreateFile(Command[1], atoi(Command[2]));
                if(iRet >= 0)
                {
                    printf("File created and opened with FD %d.\n", iRet);
                }
                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error: Invalid parameters.\n");
                }
                else if(iRet == ERR_FILE_ALREADY_EXIST)
                {
                    printf("Error: File already exists.\n");
                }
                else if(iRet == ERR_NO_INODES)
                {
                    printf("Error: No free inodes.\n");
                }
                else
                {
                    printf("Error: Unable to create file.\n");
                }
            }
            else if(strcmp(Command[0], "open") == 0)
            {
                iRet = OpenFile(Command[1], atoi(Command[2]));
                if(iRet >= 0)
                {
                    printf("File opened with FD %d.\n", iRet);
                }
                else if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error: Invalid parameters.\n");
                }
                else if(iRet == ERR_FILE_NOT_FOUND)
                {
                    printf("Error: File not found.\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error: Permission denied.\n");
                }
                else
                {
                    printf("Error: Unable to open file.\n");
                }
            }
            else if(strcmp(Command[0], "read") == 0)
            {
                memset(read_buffer, 0, sizeof(read_buffer));
                iRet = ReadFile(atoi(Command[1]), read_buffer, atoi(Command[2]));
                if(iRet > 0)
                {
                    read_buffer[iRet] = '\0';
                    printf("Data read: %s\n", read_buffer);
                }
                else if(iRet == 0)
                {
                    printf("No data to read.\n");
                }
                else if(iRet == ERR_INVALID_FD)
                {
                    printf("Error: Invalid FD.\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error: Permission denied.\n");
                }
                else
                {
                    printf("Error: Unable to read.\n");
                }
            }
            else if(strcmp(Command[0], "write") == 0)
            {
                strcpy(data, Command[2]);
                iRet = WriteFile(atoi(Command[1]), data);
                if(iRet > 0)
                {
                    printf("%d bytes written.\n", iRet);
                }
                else if(iRet == ERR_INVALID_FD)
                {
                    printf("Error: Invalid FD.\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error: Permission denied.\n");
                }
                else if(iRet == ERR_WRITE_EXCEED)
                {
                    printf("Error: Write exceeds file size.\n");
                }
                else
                {
                    printf("Error: Unable to write.\n");
                }
            }
            else
            {
                printf("Command not found. Use 'help' for list of commands.\n");
            }
        }
        else if(iCount == 4)
        {
            if(strcmp(Command[0], "lseek") == 0)
            {
                iRet = LseekFile(atoi(Command[1]), atoi(Command[2]), atoi(Command[3]));
                if(iRet >= 0)
                {
                    printf("Offset set to %d.\n", iRet);
                }
                else if(iRet == ERR_INVALID_FD)
                {
                    printf("Error: Invalid FD.\n");
                }
                else
                {
                    printf("Error: Unable to lseek.\n");
                }
            }
            else if(strcmp(Command[0], "write") == 0)
            {
                sprintf(data, "%s %s", Command[2], Command[3]);
                iRet = WriteFile(atoi(Command[1]), data);
                if(iRet > 0)
                {
                    printf("%d bytes written.\n", iRet);
                }
                else if(iRet == ERR_INVALID_FD)
                {
                    printf("Error: Invalid FD.\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error: Permission denied.\n");
                }
                else if(iRet == ERR_WRITE_EXCEED)
                {
                    printf("Error: Write exceeds file size.\n");
                }
                else
                {
                    printf("Error: Unable to write.\n");
                }
            }
            else
            {
                printf("Command not found. Use 'help' for list of commands.\n");
            }
        }
        else
        {
            // For write with more words
            if(strcmp(Command[0], "write") == 0)
            {
                data[0] = '\0';
                for(int k = 2; k < iCount; k++)
                {
                    strcat(data, Command[k]);
                    if(k < iCount - 1)
                    {
                        strcat(data, " ");
                    }
                }
                iRet = WriteFile(atoi(Command[1]), data);
                if(iRet > 0)
                {
                    printf("%d bytes written.\n", iRet);
                }
                else if(iRet == ERR_INVALID_FD)
                {
                    printf("Error: Invalid FD.\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error: Permission denied.\n");
                }
                else if(iRet == ERR_WRITE_EXCEED)
                {
                    printf("Error: Write exceeds file size.\n");
                }
                else
                {
                    printf("Error: Unable to write.\n");
                }
            }
            else
            {
                printf("Command not found. Use 'help' for list of commands.\n");
            }
        }
    }

    return 0;
}