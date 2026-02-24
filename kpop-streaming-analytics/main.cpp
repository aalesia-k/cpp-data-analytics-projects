#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int ARTIST_COUNT = 10;
const int MONTHS = 5;

struct Artist {
    string name;
    string country;
    long monthlyStreams[MONTHS];
};

// functions ------------------------------------------------------------------------------
int loadData(Artist artists[], string filename);
void displayMenu();
void displayAll(const Artist artists[], int size);
void searchArtist(const Artist artists[], int size);
void statsWithin(const Artist artists[], int size);
void statsAcross(const Artist artists[], int size);
void removeArtist(Artist artists[], int &size);
void sortByName(Artist artists[], int size);
void sortByAverageStreams(Artist artists[], int size);
double average(const long arr[], int size);

// main program ----------------------------------------------------------------------------

int main() {
    cout << fixed << setprecision(0); 
    Artist artists[ARTIST_COUNT];
    int size = loadData(artists, "kpop_data.txt");

    if (size == 0) {
        cout << "Error loading data file.\n";
        return 1;
    }

    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: displayAll(artists, size); break;
            case 2: searchArtist(artists, size); break;
            case 3: statsWithin(artists, size); break;
            case 4: statsAcross(artists, size); break;
            case 5: removeArtist(artists, size); break;
            case 6: sortByName(artists, size); break;
            case 7: sortByAverageStreams(artists, size); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}

// load the data from file --------------------------------------------
int loadData(Artist artists[], string filename) {
    ifstream file(filename);
    if (!file) return 0;

    string url;
    getline(file, url); // read the URL line
    getline(file, url); // skip any blank lines

    int count = 0;

    while (count < ARTIST_COUNT && file >> artists[count].name >> artists[count].country) {
        for (int i = 0; i < MONTHS; i++) {
            file >> artists[count].monthlyStreams[i];
        }
        count++;
    }
    return count;
}


// Menu-------------------------------------------------------------

void displayMenu() {
    cout << "\n====== K-Pop Spotify Stats ======" << endl;
    cout << "1. Display all artists" << endl;
    cout << "2. Search for an artist" << endl;
    cout << "3. Stats within one artist (average monthly streams)" << endl;
    cout << "4. Stats across all artists (highest month for chosen month)" << endl;
    cout << "5. Remove an artist" << endl;
    cout << "6. Sort artists by name" << endl;
    cout << "7. Sort artists by average monthly listeners" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose an option: ";
}

//--------------------------------------------
// Display all
//--------------------------------------------
void displayAll(const Artist artists[], int size) {
    cout << "\n" << left << setw(15) << "Name"
         << setw(15) << "Country"
         << "Monthly Streams (5 months)" << endl;
    cout << "----------------------------------------------------------" << endl;

    for (int i = 0; i < size; i++) {
        cout << left << setw(15) << artists[i].name
             << setw(15) << artists[i].country;

        for (int m = 0; m < MONTHS; m++) {
            cout << artists[i].monthlyStreams[m] << " ";
        }
        cout << endl;
    }
}

//--------------------------------------------
// Search for artist
//--------------------------------------------
void searchArtist(const Artist artists[], int size) {
    string target;
    cout << "\nEnter artist name to search: ";
    cin >> target;

    for (int i = 0; i < size; i++) {
        if (artists[i].name == target) {
            cout << "\nFound: " << artists[i].name << "\nMonthly Streams: ";
            for (int m = 0; m < MONTHS; m++) cout << artists[i].monthlyStreams[m] << " ";
            cout << endl;
            return;
        }
    }
    cout << "Artist not found." << endl;
}


// Stats within one artist --------------------------------------------
void statsWithin(const Artist artists[], int size) {
    string name;
    cout << "\nEnter artist for average monthly streams: ";
    cin >> name;

    for (int i = 0; i < size; i++) {
        if (artists[i].name == name) {
            double avg = average(artists[i].monthlyStreams, MONTHS);
            cout << "\nAverage monthly streams for " << name << ": " << avg << endl;
            return;
        }
    }
    cout << "Artist not found.\n";
}


// Stats across all artists --------------------------------------------
void statsAcross(const Artist artists[], int size) {
    int month;
    cout << "\nChoose month index (0–4): ";
    cin >> month;

    if (month < 0 || month >= MONTHS) {
        cout << "\nInvalid month.\n";
        return;
    }

    long highest = -1;
    string topArtist;

    for (int i = 0; i < size; i++) {
        if (artists[i].monthlyStreams[month] > highest) {
            highest = artists[i].monthlyStreams[month];
            topArtist = artists[i].name;
        }
    }

    cout << "\nHighest listener count in month " << month << " is "
         << highest << " by " << topArtist << endl;
}


// Remove artist --------------------------------------------
void removeArtist(Artist artists[], int &size) {
    string name;
    cout << "\nEnter artist to remove: ";
    cin >> name;

    for (int i = 0; i < size; i++) {
        if (artists[i].name == name) {
            for (int j = i; j < size - 1; j++) {
                artists[j] = artists[j + 1];
            }
            size--;
            cout << "\nThe artist" << name << " removed.\n";
            return;
        }
    }
    cout << "\nArtist not found.\n";
}


// Sort by name --------------------------------------------
void sortByName(Artist artists[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (artists[j].name < artists[i].name) {
                swap(artists[j], artists[i]);
            }
        }
    }
    cout << "\nSorted alphabetically.\n";
}


// Sort by average streams --------------------------------------------
void sortByAverageStreams(Artist artists[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            double avg1 = average(artists[i].monthlyStreams, MONTHS);
            double avg2 = average(artists[j].monthlyStreams, MONTHS);

            if (avg2 > avg1) {  
                swap(artists[i], artists[j]);
            }
        }
    }
    cout << "\nSorted by highest average monthly listeners.\n";
}


// Average helper function --------------------------------------------
double average(const long arr[], int size) {
    long sum = 0;
    for (int i = 0; i < size; i++) sum += arr[i];
    return sum * 1.0 / size;
}


