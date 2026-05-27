#include <iostream>
#include <cstring>
using namespace std;

const int MAX_USERS = 10;
const int MAX_MOVIES = 50;

// User data
char usernames[MAX_USERS][50];
char passwords[MAX_USERS][50];
int userCount = 0;
int currentUser = -1;

// Movie data for each user
char movieNames[MAX_USERS][MAX_MOVIES][50];
int movieRatings[MAX_USERS][MAX_MOVIES];
char movieReviews[MAX_USERS][MAX_MOVIES][200];
bool movieWatchlist[MAX_USERS][MAX_MOVIES];
int movieCount[MAX_USERS] = {0};

// ===== HELPER FUNCTIONS =====

int findMovie(char name[]) {
    for (int i = 0; i < movieCount[currentUser]; i++) {
        if (strcmp(movieNames[currentUser][i], name) == 0) {
            return i;
        }
    }
    return -1;
}

void displayMovie(int index) {
    cout << "\nMovie Found!\n";
    cout << "Name: " << movieNames[currentUser][index] << endl;
    cout << "Rating: ";
    if (movieRatings[currentUser][index] == 0) {
        cout << "No rating\n";
    } else {
        cout << movieRatings[currentUser][index] << "/10\n";
    }
    cout << "Review: " << movieReviews[currentUser][index] << endl;
}

// ===== USER MANAGEMENT =====

void registerUser() {
    if (userCount >= MAX_USERS) {
        cout << "Maximum users reached!\n";
        return;
    }
    
    char user[50], pass[50];
    cout << "Enter username: ";
    cin >> user;
    
    // Check if username exists
    for (int i = 0; i < userCount; i++) {
        if (strcmp(usernames[i], user) == 0) {
            cout << "Username already exists!\n";
            return;
        }
    }
    
    cout << "Enter password: ";
    cin >> pass;
    
    strcpy(usernames[userCount], user);
    strcpy(passwords[userCount], pass);
    movieCount[userCount] = 0;
    
    userCount++;
    cout << "Registration successful!\n";
}

void loginUser() {
    char user[50], pass[50];
    cout << "Enter username: ";
    cin >> user;
    cout << "Enter password: ";
    cin >> pass;
    
    for (int i = 0; i < userCount; i++) {
        if (strcmp(usernames[i], user) == 0 && strcmp(passwords[i], pass) == 0) {
            currentUser = i;
            cout << "Login successful! Welcome " << user << "!\n";
            return;
        }
    }
    
    cout << "Invalid username or password!\n";
}

void logoutUser() {
    cout << "Logged out successfully!\n";
    currentUser = -1;
}

// ===== MOVIE MANAGEMENT =====

void addMovie() {
    if (movieCount[currentUser] >= MAX_MOVIES) {
        cout << "Movie list is full!\n";
        return;
    }
    
    char name[50];
    cout << "Enter movie name: ";
    cin >> name;
    
    if (findMovie(name) != -1) {
        cout << "Movie already exists!\n";
        return;
    }
    
    int idx = movieCount[currentUser];
    strcpy(movieNames[currentUser][idx], name);
    movieRatings[currentUser][idx] = 0;
    strcpy(movieReviews[currentUser][idx], "None");
    movieWatchlist[currentUser][idx] = false;
    
    movieCount[currentUser]++;
    cout << "Movie added!\n";
}

void searchMovie() {
    char search[50];
    cout << "Enter movie name: ";
    cin >> search;
    
    int index = findMovie(search);
    if (index != -1) {
        displayMovie(index);
    } else {
        cout << "Movie not found.\n";
    }
}

void rateMovie() {
    char search[50];
    cout << "Enter movie name: ";
    cin >> search;
    
    int index = findMovie(search);
    if (index == -1) {
        cout << "Movie not found.\n";
        return;
    }
    
    int rating;
    do {
        cout << "Enter rating (1-10): ";
        cin >> rating;
        
        if (rating < 1 || rating > 10) {
            cout << "Invalid! Enter 1-10.\n";
        }
    } while (rating < 1 || rating > 10);
    
    movieRatings[currentUser][index] = rating;
    cout << "Rating saved!\n";
}

void reviewMovie() {
    char search[50];
    cout << "Enter movie name: ";
    cin >> search;
    
    int index = findMovie(search);
    if (index == -1) {
        cout << "Movie not found.\n";
        return;
    }
    
    cout << "Enter review: ";
    cin.ignore();
    cin.getline(movieReviews[currentUser][index], 200);
    cout << "Review saved!\n";
}

void addToWatchlist() {
    char search[50];
    cout << "Enter movie name: ";
    cin >> search;
    
    int index = findMovie(search);
    if (index == -1) {
        cout << "Movie not found.\n";
        return;
    }
    
    if (movieWatchlist[currentUser][index]) {
        cout << "Already in watchlist!\n";
    } else {
        movieWatchlist[currentUser][index] = true;
        cout << "Added to watchlist!\n";
    }
}

void viewWatchlist() {
    cout << "\n--- YOUR WATCHLIST ---\n";
    
    bool hasMovies = false;
    for (int i = 0; i < movieCount[currentUser]; i++) {
        if (movieWatchlist[currentUser][i]) {
            cout << movieNames[currentUser][i] << " | Rating: ";
            if (movieRatings[currentUser][i] == 0) {
                cout << "No rating";
            } else {
                cout << movieRatings[currentUser][i] << "/10";
            }
            cout << " | Review: " << movieReviews[currentUser][i] << endl;
            hasMovies = true;
        }
    }
    
    if (!hasMovies) {
        cout << "Watchlist is empty!\n";
    }
}

void viewStats() {
    cout << "\n--- MOVIE STATISTICS ---\n";
    
    int total = movieCount[currentUser];
    
    if (total == 0) {
        cout << "No movies!\n";
        return;
    }
    
    int ratedCount = 0;
    int totalRating = 0;
    
    for (int i = 0; i < total; i++) {
        if (movieRatings[currentUser][i] > 0) {
            totalRating += movieRatings[currentUser][i];
            ratedCount++;
        }
    }
    
    cout << "Total Movies: " << total << endl;
    cout << "Rated Movies: " << ratedCount << endl;
    cout << "Unrated Movies: " << (total - ratedCount) << endl;
    
    if (ratedCount > 0) {
        float average = (float)totalRating / ratedCount;
        cout << "Average Rating: " << average << "/10\n";
    } else {
        cout << "Average Rating: No ratings yet\n";
    }
    
    cout << "\n--- ALL MOVIES ---\n";
    for (int i = 0; i < total; i++) {
        cout << (i + 1) << ". " << movieNames[currentUser][i] << " - Rating: ";
        if (movieRatings[currentUser][i] == 0) {
            cout << "No rating\n";
        } else {
            cout << movieRatings[currentUser][i] << "/10\n";
        }
    }
}

void deleteMovie() {
    char search[50];
    cout << "Enter movie name: ";
    cin >> search;
    
    int index = findMovie(search);
    if (index == -1) {
        cout << "Movie not found.\n";
        return;
    }
    
    cout << "Delete '" << movieNames[currentUser][index] << "'? (y/n): ";
    char confirm;
    cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        for (int i = index; i < movieCount[currentUser] - 1; i++) {
            strcpy(movieNames[currentUser][i], movieNames[currentUser][i + 1]);
            movieRatings[currentUser][i] = movieRatings[currentUser][i + 1];
            strcpy(movieReviews[currentUser][i], movieReviews[currentUser][i + 1]);
            movieWatchlist[currentUser][i] = movieWatchlist[currentUser][i + 1];
        }
        movieCount[currentUser]--;
        cout << "Movie deleted!\n";
    }
}

// ===== MENU FUNCTIONS =====

void showLoginMenu() {
    cout << "\n===== MOVIE TOOL =====\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << "Enter choice: ";
}

void showMovieMenu() {
    cout << "\n===== MOVIE TOOL (User: " << usernames[currentUser] << ") =====\n";
    cout << "1. Add Movie\n";
    cout << "2. Search Movie\n";
    cout << "3. Rate Movie\n";
    cout << "4. Give Review\n";
    cout << "5. Add to Watchlist\n";
    cout << "6. View Watchlist\n";
    cout << "7. View Statistics\n";
    cout << "8. Delete Movie\n";
    cout << "9. Logout\n";
    cout << "Enter choice: ";
}

// ===== MAIN PROGRAM =====

int main() {
    int choice;
    
    cout << "Welcome to Movie Management Tool!\n";
    
    while (true) {
        if (currentUser == -1) {
            showLoginMenu();
            cin >> choice;
            
            if (choice == 1) {
                registerUser();
            }
            else if (choice == 2) {
                loginUser();
            }
            else if (choice == 3) {
                cout << "Goodbye!\n";
                break;
            }
            else {
                cout << "Invalid choice!\n";
            }
        }
        else {
            showMovieMenu();
            cin >> choice;
            
            if (choice == 1) {
                addMovie();
            }
            else if (choice == 2) {
                searchMovie();
            }
            else if (choice == 3) {
                rateMovie();
            }
            else if (choice == 4) {
                reviewMovie();
            }
            else if (choice == 5) {
                addToWatchlist();
            }
            else if (choice == 6) {
                viewWatchlist();
            }
            else if (choice == 7) {
                viewStats();
            }
            else if (choice == 8) {
                deleteMovie();
            }
            else if (choice == 9) {
                logoutUser();
            }
            else {
                cout << "Invalid choice!\n";
            }
        }
    }
    
    return 0;
}
