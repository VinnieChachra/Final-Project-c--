#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>

// Structure to represent an Anime
struct Anime
{
    std::string title;
    std::vector<std::string> genres;
    int rating; // From 1 to 10
};

// Helper function to convert a string to lowercase
std::string toLowerCase(const std::string &str)
{
    std::string lowerStr;
    for (char c : str)
    {
        lowerStr += std::tolower(c);
    }
    return lowerStr;
}

// Function to recommend anime based on multiple genres and a minimum rating
std::vector<std::string> recommendAnime(const std::vector<Anime> &animes, const std::vector<std::string> &preferredGenres, int minRating)
{
    std::vector<std::pair<std::string, int>> recommendations; // Pair of title and match score

    for (const auto &anime : animes)
    {
        int matchScore = 0;
        for (const auto &genre : anime.genres)
        {
            if (std::find(preferredGenres.begin(), preferredGenres.end(), toLowerCase(genre)) != preferredGenres.end())
            {
                matchScore++;
            }
        }
        if (matchScore > 0 && anime.rating >= minRating)
        {
            recommendations.push_back({anime.title, matchScore});
        }
    }

    // Sort recommendations by match score (higher first) and then by rating (higher first)
    std::sort(recommendations.begin(), recommendations.end(), [](const auto &a, const auto &b)
              { return a.second == b.second ? a.first > b.first : a.second > b.second; });

    // Extract titles from sorted recommendations
    std::vector<std::string> recommendedTitles;
    for (const auto &recommendation : recommendations)
    {
        recommendedTitles.push_back(recommendation.first);
    }

    return recommendedTitles;
}

int main()
{
    // Example data
    std::vector<Anime> animes = {
        {"Naruto", {"Action", "Adventure"}, 9},
        {"My Hero Academia", {"Action", "Superhero"}, 8},
        {"Your Lie in April", {"Romance", "Drama"}, 10},
        {"Fruits Basket", {"Romance", "Slice of Life"}, 9},
        {"Attack on Titan", {"Action", "Fantasy"}, 10},
        {"One Piece", {"Action", "Adventure"}, 9},
        {"Clannad", {"Romance", "Drama", "Slice of Life"}, 8},
        {"Demon Slayer: Kimetsu no Yaiba", {"Action", "Adventure", "Demons"}, 9},
        {"Death Note", {"Thriller", "Supernatural", "Psychological"}, 9},
        {"Sword Art Online", {"Action", "Adventure", "Fantasy"}, 8},
        {"Fullmetal Alchemist: Brotherhood", {"Action", "Adventure", "Fantasy"}, 10},
        {"Tokyo Ghoul", {"Action", "Horror", "Supernatural"}, 7},
        {"Steins;Gate", {"Sci-Fi", "Thriller", "Psychological"}, 9},
        {"Dragon Ball Z", {"Action", "Adventure", "Martial Arts"}, 8},
        {"One Punch Man", {"Action", "Comedy", "Superhero"}, 9},
        {"Neon Genesis Evangelion", {"Mecha", "Psychological", "Drama"}, 9},
        {"Hunter x Hunter", {"Action", "Adventure", "Fantasy"}, 9},
        {"Cowboy Bebop", {"Action", "Sci-Fi", "Adventure"}, 9},
        {"Code Geass: Lelouch of the Rebellion", {"Action", "Mecha", "Military"}, 10},
        {"Bleach", {"Action", "Adventure", "Supernatural"}, 8},
        {"Fairy Tail", {"Action", "Adventure", "Fantasy"}, 7},
        {"Mob Psycho 100", {"Action", "Comedy", "Supernatural"}, 8},
        {"K-On!", {"Music", "Slice of Life", "Comedy"}, 8},
        {"Toradora!", {"Romance", "Slice of Life", "Comedy"}, 9},
        {"Haikyuu!!", {"Sports", "Shounen", "Drama"}, 9},
        {"Re:Zero - Starting Life in Another World", {"Fantasy", "Psychological", "Drama"}, 9},
        {"Sword Art Online: Alicization", {"Action", "Adventure", "Fantasy"}, 7},
        {"Violet Evergarden", {"Drama", "Fantasy", "Slice of Life"}, 10},
        {"The Promised Neverland", {"Thriller", "Horror", "Mystery"}, 9},
        {"Kimi no Na wa (Your Name)", {"Romance", "Drama", "Supernatural"}, 10},
        {"Spirited Away", {"Fantasy", "Adventure", "Supernatural"}, 10},
        {"Howl's Moving Castle", {"Fantasy", "Adventure", "Romance"}, 9},
        {"Monogatari Series", {"Mystery", "Supernatural", "Romance"}, 9},
        {"A Silent Voice", {"Drama", "Romance", "Slice of Life"}, 10},
        {"Anohana: The Flower We Saw That Day", {"Drama", "Slice of Life", "Supernatural"}, 9},
        {"Shingeki no Kyojin: The Final Season", {"Action", "Drama", "Fantasy"}, 10},
        {"Mushoku Tensei: Jobless Reincarnation", {"Fantasy", "Adventure", "Isekai"}, 9},
        {"Black Clover", {"Action", "Adventure", "Fantasy"}, 8},
        {"Jujutsu Kaisen", {"Action", "Supernatural", "Demons"}, 9}};

    // User input
    std::vector<std::string> genres;
    std::string genre;
    int rating;

    std::cout << "Enter your preferred genres (type 'done' when finished): ";
    while (std::cin >> genre && genre != "done")
    {
        genres.push_back(toLowerCase(genre));
    }

    std::cout << "Enter your minimum acceptable rating (1-10): ";
    std::cin >> rating;

    // Get recommendations
    auto recommendations = recommendAnime(animes, genres, rating);

    std::cout << "Recommended Anime:" << std::endl;
    for (const auto &title : recommendations)
    {
        std::cout << title << std::endl;
    }

    if (recommendations.empty())
    {
        std::cout << "No anime match your preferences." << std::endl;
    }

    return 0;
}
