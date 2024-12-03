import java.util.LinkedList;

public class ContactHashTable {
    private static final int TABLE_SIZE = 1009;
    private Contact[] table;
    
    
    static class Contact {
        String name;
        String phoneNumber;
        
        Contact(String name, String phoneNumber) {
            this.name = name;
            this.phoneNumber = phoneNumber;
        }
        @Override
        public String toString() {
            return name+": "+phoneNumber;
        }

    }
    
    public ContactHashTable() {
        table = new Contact[TABLE_SIZE];
    }
    
    // Hash function as provided in the assignment
    public static long calc_hash(String key, int table_size) {
        int l = key.length();
        long hash = 0; //in java, long is like long long in C & cpp
        //long longValue = 9223372036854775807L;

        for (int i = 0; i < l; i++) {
            hash += Character.getNumericValue(key.charAt(i));
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }
        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);

        return (hash > 0 ? hash : -hash) % table_size;
    }
    
    // Insert a new contact
    public void insert(String name, String phoneNumber) {
        int index = (int)calc_hash(name, TABLE_SIZE);
        int initialIndex= index;
        //I turn it to int cuz array's size have to be of type int
        //This conversion is safe because the final result must be =<1009 because of the modulus operation at the end of the
        //hash function
        
        while(true){
            if( table[index] == null ){
                table[index]= new Contact(name, phoneNumber);
                break;
            }
            else if (table[index].name.equals(name)){
                System.out.println("A contact with this name already exists!");
                break;
            }
            else {
                //This line is for circular indexing (for linear probing)
                index= index==TABLE_SIZE-1 ? 0 : index+1;
                if(index == initialIndex){
                    System.out.println("The HashTable is full!");
                    break;
                }
            }   
        }
    }
    
    // Search for a contact by name
    public int search(String name) {
        int index = (int)calc_hash(name, TABLE_SIZE);
        int initialIndex= index;

        while(table[index]!=null){
            if(table[index].name.equals(name)){
                System.out.println(table[index]);
                return index;
            }
            index= index==TABLE_SIZE-1 ? 0 : index+1; //circular indexing
            if(index == initialIndex){
                break;
            }
        }
        System.out.println("No contact was found!");
        return -1;

    }

    
    // Delete a contact by name
    public void delete(String name) {
        int index= search(name);
        if (index == -1) {
            System.out.println("No contact is found!");
        }
        else {
            table[index]= null;
            System.out.println("Contact is deleted successfully.");
        }
    }


    public void update(String newNum, String name){
        int index= search(name);
        if(index == -1){
            System.out.println("No contact is found!");
        }
        else{
            table[index].phoneNumber= newNum;
            System.out.println("Contact is updated successfully.");
        }
    }
    // Display all contacts
    public void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if(table[i]!=null)
                System.out.println(table[i]);
        }
    }
    
    public static void main(String[] args) {
        ContactHashTable phoneList = new ContactHashTable();
        
        phoneList.insert("Alice", "123-456-7890");
        phoneList.insert("Bob", "234-567-8901");
        System.out.println("-------------------------------------\n");
        System.out.println("Searching for Alice: ");
        phoneList.search("Alice");
        System.out.println("-------------------------------------\n");
        phoneList.display();
        System.out.println("-------------------------------------\n");
        phoneList.delete("Bob");
        //The search() method within the delete() will print Bob's info & then delete the contact
        System.out.println("-------------------------------------\n");
        phoneList.display();
        //Only alice exists in the phoneList so far.
        System.out.println("-------------------------------------\n");
        phoneList.update("987-654-3210","Alice");
        phoneList.search("Alice");
        System.out.println("-------------------------------------\n");
        phoneList.insert("Stefany", "321-543-0987");
        phoneList.display();
    }
}
