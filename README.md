# Movie Management System — C++

A console-based movie management tool built in C++ that lets multiple users register, log in, and manage their own personal movie libraries independently.

---

## Features

**User Authentication** — register and log in with a username and password. Each user's data is completely separate; up to 10 accounts can exist simultaneously.

**Movie Library** — add movies to your personal list and search for them by name. The system prevents duplicates and handles up to 50 movies per user.

**Ratings & Reviews** — rate any movie on a scale of 1–10 and attach a written review. Both can be updated at any time.

**Watchlist** — mark movies you plan to watch. View your full watchlist with ratings and reviews at a glance.

**Viewing Statistics** — see a summary of your library: total movies, how many are rated vs unrated, average rating across all rated films, and a full list with scores.

**Delete Movies** — remove a movie from your library with a confirmation prompt before deletion.

---

## How to Run

Compile with any standard C++ compiler:

```bash
g++ PFPROJECTFINAL.cpp -o movie_manager
./movie_manager
```

No external libraries or dependencies required.

---

## Usage

On launch you'll see a login menu. Register a new account or log in to an existing one. Once logged in, a menu gives you access to all movie management features. Type the corresponding number and follow the prompts.

```
===== MOVIE TOOL =====
1. Register
2. Login
3. Exit

===== MOVIE TOOL (User: rahma) =====
1. Add Movie
2. Search Movie
3. Rate Movie
4. Give Review
5. Add to Watchlist
6. View Watchlist
7. View Statistics
8. Delete Movie
9. Logout
```

---

## Technical Details

- Language: C++
- Data storage: in-memory arrays (no file I/O; data resets on exit)
- Concepts used: arrays, functions, loops, string handling (`cstring`), modular programming, CRUD operations
- Constraints: max 10 users, max 50 movies per user, movie names up to 50 characters, reviews up to 200 characters

---

## Academic Context

This project was developed as the final project for the Programming Fundamentals (PF) course at FAST-NUCES Islamabad.
