#!/bin/bash

create()
{
    touch "addressbook.txt"
    echo "Address book file created successfully."
}

insert()
{
    echo "Enter name:"
    read name
    echo "Enter phone_no:"
    read phone_no
    echo "Enter address:"
    read address
    echo "$name | $phone_no | $address" >> addressbook.txt
    echo "Record inserted successfully."
}

view()
{
    if [ -f "addressbook.txt" ]; then
        echo "--- Address Book Records ---"
        cat addressbook.txt
        echo "----------------------------"
    else
        echo "Address book file does not exist yet. Please create it first."
    fi
}

modify()
{
    echo "Enter name that you want to modify:"
    read name
    
    if [ -f "addressbook.txt" ]; then
        grep -v "^$name |" addressbook.txt > addressbook1.txt
        cp addressbook1.txt addressbook.txt
        rm addressbook1.txt
        
        echo "Enter new name:"
        read name
        echo "Enter new phone_no:"
        read phone_no
        echo "Enter new address:"
        read address
        echo "$name | $phone_no | $address" >> addressbook.txt
        echo "Record modified successfully."
    else
        echo "Address book file does not exist."
    fi
}

delete()
{
    echo "Enter name that you want to delete:"
    read name
    
    if [ -f "addressbook.txt" ]; then
        sed -i "/^$name /d" addressbook.txt
        echo "Record deleted successfully."
    else
        echo "Address book file does not exist."
    fi
}
choice=0
while [ $choice -lt 6 ]
do
    echo ""
    echo "1. create"
    echo "2. insert"
    echo "3. view"
    echo "4. modify"
    echo "5. delete"
    echo "6. exit"
    echo "Enter Your Choice:"
    read choice
    
    case $choice in
        1) 
            echo "create file"
            create 
            ;;
        2) 
            echo "insert"
            insert
            ;;
        3) 
            echo "view"
            view
            ;;
        4) 
            echo "modify"
            modify 
            ;;
        5) 
            echo "delete"
            delete 
            ;;
        6) 
            echo "exit"
            exit 0
            ;;
        *) 
            echo "Invalid choice. Please enter a number between 1 and 6." 
            ;;
    esac
done
