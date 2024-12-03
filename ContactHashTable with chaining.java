import java.util.LinkedList;

public class ContactHashTable {
    private static final int TABLE_SIZE = 1009;
    private LinkedList<Contact>[] table;
    static class Contact {
        String name;
        LinkedList<String> phoneNumber;
        
        Contact(String name, String phoneNumber) {
            this.name = name;
            this.phoneNumber = new LinkedList<>();            
            this.phoneNumber.add(phoneNumber.replaceAll("[^\\d-]", ""));
        }
        @Override
        public String toString() {
            String nums="";
            for (String number : phoneNumber) {  //for each number in the numbers list.
                nums += number + ", ";
            }
            
            // Remove the trailing comma and space
            if (!nums.isEmpty()) {
                nums = nums.substring(0, nums.length() - 2);
            }
            return name+": "+nums;
        }

    }
    
    public ContactHashTable() {
        table = new LinkedList[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = new LinkedList<>();
        }
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
        phoneNumber= phoneNumber.replaceAll("[^\\d-]", "");
        long index = calc_hash(name, TABLE_SIZE);
        LinkedList<Contact> bucket = table[(int) index];
        
        for (Contact contact : bucket) {
            if (contact.name.equals(name)) {
                System.out.println("Contact with this name already exists. Use update to change the number.");
                return;
            }
        }
        bucket.add(new Contact(name, phoneNumber));
    }
    
    // Search for a contact by name
    public void search(String name) {
        long index = calc_hash(name, TABLE_SIZE);
        LinkedList<Contact> bucket = table[(int) index];
        
        for (Contact contact : bucket) {
            if (contact.name.equals(name)) {
                System.out.println(contact);
                return;
            }
        }
        System.out.println("No contact was found!");
    }
    
    // Delete a contact by name
    public void delete(String name) {
        long index = calc_hash(name, TABLE_SIZE);
        LinkedList<Contact> bucket = table[(int) index];
        
        for (Contact contact : bucket) {
            if (contact.name.equals(name)) {
                bucket.remove(contact);
                System.out.println("Contact deleted.");
                return;
            }
        }
        System.out.println("Contact not found.");
    }
    
    // Adding a number to a contact
    public void addNum(String name, String newPhoneNumber) {
        newPhoneNumber=newPhoneNumber.replaceAll("[^\\d-]", "");
        long index = calc_hash(name, TABLE_SIZE);
        LinkedList<Contact> bucket = table[(int) index];
        
        for (Contact contact : bucket) {
            if (contact.name.equals(name)) {
                contact.phoneNumber.add(newPhoneNumber);
                System.out.println("Contact updated.");
                return;
            }
        }
        System.out.println("Contact not found.");
    }
    // Deleting a number
    public void delNum(String name, String delMe) {
        delMe= delMe.replaceAll("[^\\d-]", "");
        long index = calc_hash(name, TABLE_SIZE);
        LinkedList<Contact> bucket = table[(int) index];
        
        for (Contact contact : bucket) {
            if (contact.name.equals(name)) {
                for(String num : contact.phoneNumber){
                    if(num.equals(delMe)){
                        contact.phoneNumber.remove(num);
                        System.out.println(delMe + " from the contact \""+ name +"\" has been deleted successfully.");
                        return;
                    }
                }
                System.out.println("Contact is found, but your number doesn't exist.");
                return;
            }  
        }
        System.out.println("Contact not found.");
    }

    // Display all contacts
    public void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            for (Contact contact : table[i]) {
                System.out.println(contact);
            }
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
        phoneList.addNum("Alice", "987-654-3210");
        System.out.println("After update, Alice's contact: ");
        phoneList.search("Alice");
        System.out.println("-------------------------------------\n");
        phoneList.display();
        System.out.println("-------------------------------------\n");
        phoneList.delete("Bob");
        phoneList.display();
        System.out.println("-------------------------------------\n");
        phoneList.delNum("Alice", "987-654-32");
        System.out.println("-------------------------------------\n");
        phoneList.delNum("Alice", "987-654-3210");
        System.out.println("-------------------------------------\n");
        phoneList.display();
    }
}
