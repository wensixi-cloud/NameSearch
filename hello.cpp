// NameSearch demo program
// - Generates 100 unique random names from a large list
// - Sorts the names alphabetically
// - Performs repeated binary searches on user-provided queries
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <set>

// NameManager encapsulates generation, sorting, display, and searching of names
class NameManager {
private:
    // Holds the current working set of unique names
    std::vector<std::string> names;
    // Backing database of popular names to sample from
    std::vector<std::string> popularNames;
    
    // Initializes the popular names database used for random sampling
    void initializePopularNames() {
        popularNames = {
            "James", "Mary", "John", "Patricia", "Robert", "Jennifer", "Michael", "Linda", "William", "Elizabeth",
            "David", "Barbara", "Richard", "Susan", "Joseph", "Jessica", "Thomas", "Sarah", "Christopher", "Karen",
            "Charles", "Nancy", "Daniel", "Lisa", "Matthew", "Betty", "Anthony", "Helen", "Mark", "Sandra",
            "Donald", "Donna", "Steven", "Carol", "Paul", "Ruth", "Andrew", "Sharon", "Joshua", "Michelle",
            "Kenneth", "Laura", "Kevin", "Kimberly", "Brian", "Deborah", "George", "Dorothy", "Timothy", "Amy",
            "Ronald", "Angela", "Jason", "Ashley", "Edward", "Brenda", "Jeffrey", "Emma", "Ryan", "Olivia",
            "Jacob", "Cynthia", "Gary", "Marie", "Nicholas", "Janet", "Eric", "Catherine", "Jonathan", "Frances",
            "Stephen", "Christine", "Larry", "Samantha", "Justin", "Debra", "Scott", "Rachel", "Brandon", "Carolyn",
            "Benjamin", "Janet", "Samuel", "Virginia", "Gregory", "Maria", "Frank", "Heather", "Raymond", "Diane",
            "Alexander", "Julie", "Patrick", "Joyce", "Jack", "Victoria", "Dennis", "Kelly", "Jerry", "Christina",
            "Tyler", "Joan", "Aaron", "Evelyn", "Jose", "Judith", "Henry", "Megan", "Adam", "Cheryl",
            "Nathan", "Andrea", "Zachary", "Hannah", "Kyle", "Jacqueline", "Noah", "Martha", "Alan", "Gloria",
            "Ethan", "Teresa", "Jeremy", "Sara", "Mason", "Janice", "Christian", "Julia", "Sean", "Marie",
            "Austin", "Madison", "Carl", "Grace", "Arthur", "Judy", "Lawrence", "Theresa", "Joe", "Beverly",
            "Noah", "Denise", "Roger", "Marilyn", "Juan", "Amber", "Wayne", "Danielle", "Roy", "Rose",
            "Ralph", "Brittany", "Eugene", "Diana", "Louis", "Abigail", "Philip", "Jane", "Bobby", "Lori",
            "Johnny", "Tammy", "Lawrence", "Marilyn", "Wayne", "Danielle", "Roy", "Rose", "Ralph", "Brittany",
            "Eugene", "Diana", "Louis", "Abigail", "Philip", "Jane", "Bobby", "Lori", "Johnny", "Tammy",
            "Aaron", "Michelle", "Jose", "Laura", "Henry", "Sarah", "Adam", "Kimberly", "Nathan", "Andrea",
            "Zachary", "Hannah", "Kyle", "Jacqueline", "Noah", "Martha", "Alan", "Gloria", "Ethan", "Teresa",
            "Jeremy", "Sara", "Mason", "Janice", "Christian", "Julia", "Sean", "Marie", "Austin", "Madison",
            "Carl", "Grace", "Arthur", "Judy", "Lawrence", "Theresa", "Joe", "Beverly", "Noah", "Denise",
            "Roger", "Marilyn", "Juan", "Amber", "Wayne", "Danielle", "Roy", "Rose", "Ralph", "Brittany",
            "Eugene", "Diana", "Louis", "Abigail", "Philip", "Jane", "Bobby", "Lori", "Johnny", "Tammy",
            "Aaron", "Michelle", "Jose", "Laura", "Henry", "Sarah", "Adam", "Kimberly", "Nathan", "Andrea",
            "Zachary", "Hannah", "Kyle", "Jacqueline", "Noah", "Martha", "Alan", "Gloria", "Ethan", "Teresa",
            "Jeremy", "Sara", "Mason", "Janice", "Christian", "Julia", "Sean", "Marie", "Austin", "Madison",
            "Carl", "Grace", "Arthur", "Judy", "Lawrence", "Theresa", "Joe", "Beverly", "Noah", "Denise",
            "Roger", "Marilyn", "Juan", "Amber", "Wayne", "Danielle", "Roy", "Rose", "Ralph", "Brittany",
            "Eugene", "Diana", "Louis", "Abigail", "Philip", "Jane", "Bobby", "Lori", "Johnny", "Tammy",
            "Aaron", "Michelle", "Jose", "Laura", "Henry", "Sarah", "Adam", "Kimberly", "Nathan", "Andrea",
            "Zachary", "Hannah", "Kyle", "Jacqueline", "Noah", "Martha", "Alan", "Gloria", "Ethan", "Teresa",
            "Jeremy", "Sara", "Mason", "Janice", "Christian", "Julia", "Sean", "Marie", "Austin", "Madison",
            "Carl", "Grace", "Arthur", "Judy", "Lawrence", "Theresa", "Joe", "Beverly", "Noah", "Denise",
            "Roger", "Marilyn", "Juan", "Amber", "Wayne", "Danielle", "Roy", "Rose", "Ralph", "Brittany",
            "Eugene", "Diana", "Louis", "Abigail", "Philip", "Jane", "Bobby", "Lori", "Johnny", "Tammy"
        };
    }

public:
    // Constructs a NameManager and prepares the popular names database
    NameManager() {
        initializePopularNames();
    }
    
    // Generates exactly 100 unique names sampled from popularNames
    // Uses a set to guarantee uniqueness across selections
    void generateUniqueNames() {
        names.clear();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, popularNames.size() - 1);
        std::set<std::string> usedNames;
        
        std::cout << "Generating 100 unique random popular names..." << std::endl;
        while (names.size() < 100) {
            int randomIndex = dis(gen);
            std::string selectedName = popularNames[randomIndex];
            
            // Only add if the name hasn't been used before
            if (usedNames.find(selectedName) == usedNames.end()) {
                names.push_back(selectedName);
                usedNames.insert(selectedName);
            }
        }
    }
    
    // Sorts the current names vector in ascending (A-Z) lexicographic order
    void sortNamesAlphabetically() {
        std::sort(names.begin(), names.end());
    }
    
    // Prints all names on a single line, prefixed by a title
    void displayNames(const std::string& title) const {
        std::cout << title << ": ";
        for (int i = 0; i < names.size(); i++) {
            std::cout << names[i];
            if (i < names.size() - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    
    // Performs binary search over the sorted names vector
    // Returns the 0-based index if found, or -1 if not found
    int binarySearch(const std::string& searchName) const {
        int left = 0;
        int right = names.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (names[mid] == searchName) {
                return mid;
            } else if (names[mid] < searchName) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1; // Not found
    }
    
    // Invokes binary search and prints a user-friendly result line
    void searchName(const std::string& searchName) const {
        int index = binarySearch(searchName);
        
        if (index != -1) {
            std::cout << "Found " << searchName << " at index " << index << std::endl;
        } else {
            std::cout << "Not found. Returned " << index << std::endl;
        }
    }
    
    // Provides read-only access to the current names vector
    const std::vector<std::string>& getNames() const {
        return names;
    }
    
    // Returns the number of names currently stored
    size_t getNamesSize() const {
        return names.size();
    }
};

int main() {
    // Create NameManager object to manage the workflow
    NameManager nameManager;
    
    // 1) Generate data
    nameManager.generateUniqueNames();
    
    // 2) Show unsorted set (for reference)
    nameManager.displayNames("Generated names");
    
    // 3) Sort for deterministic order and for binary search precondition
    nameManager.sortNamesAlphabetically();
    
    // 4) Show sorted list users will search against
    nameManager.displayNames("Sorted names in alphabetical order");
    
    // 5) Repeatedly accept queries and search using binary search
    std::string searchName;
    
    while (true) {
        std::cout << "Enter a name to search for: ";
        std::cin >> searchName;
        
        // Search for the name
        nameManager.searchName(searchName);
    }
    
    return 0;
}