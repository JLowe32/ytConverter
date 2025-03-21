#include <iostream>
#include <string>
#include <cstdlib>  
#include <curl/curl.h>
#include "nlohmann/json.hpp"

// Function to store HTTP response data
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

// Function to fetch YouTube video page HTML
std::string fetchYouTubeData(const std::string& videoURL) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, videoURL.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "cURL failed: " << curl_easy_strerror(res) << std::endl;
        }
        
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}

// Function to parse YouTube metadata from HTML response
void parseYouTubeData(const std::string& htmlContent, std::string& videoTitle, std::string& videoAuthor, std::string& videoDuration) {
    size_t jsonStart = htmlContent.find("ytInitialPlayerResponse");
    if (jsonStart == std::string::npos) {
        std::cerr << "Could not find metadata in response." << std::endl;
        return;
    }

    size_t jsonEnd = htmlContent.find("};", jsonStart);
    if (jsonEnd == std::string::npos) {
        std::cerr << "JSON parsing error." << std::endl;
        return;
    }

    std::string jsonString = htmlContent.substr(jsonStart + 26, jsonEnd - jsonStart - 24);

    try {
        auto json = nlohmann::json::parse(jsonString);
        videoTitle = json["videoDetails"]["title"];
        videoAuthor = json["videoDetails"]["author"];
        videoDuration = json["videoDetails"]["lengthSeconds"];
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
}

// Function to download video using yt-dlp
void downloadYouTubeAudio(const std::string& videoID) {
    std::string command = "yt-dlp -x --audio-format mp3 https://www.youtube.com/watch?v=" + videoID;
    std::cout << "Downloading and converting to MP3...\n";
    int result = system(command.c_str());

    if (result != 0) {
        std::cerr << "Download failed! Make sure yt-dlp and ffmpeg are installed.\n";
    } else {
        std::cout << "Download complete! Audio saved as MP3.\n";
    }
}


int main() {

    std::string videoURL;
    std::cout << "Enter YouTube Video URL: ";
    std::cin >> videoURL;

    // Check if the URL is a valid YouTube link
    if (videoURL.find("https://www.youtube.com/watch?v=") != std::string::npos) {

        std::cout << "Fetching video data from: " << videoURL << std::endl;

        std::string htmlContent = fetchYouTubeData(videoURL);
        if (htmlContent.empty()) {
            std::cerr << "Failed to fetch data!" << std::endl;
            return 1;
        }

        std::string title, author, duration;
        parseYouTubeData(htmlContent, title, author, duration);

        std::cout << "\nVideo Information:\n";
        std::cout << "Title: " << title << "\n";
        std::cout << "Uploader: " << author << "\n";
        std::cout << "Duration: " << duration << " seconds\n\n";

        char choice;
        std::cout << "Do you want to download this video? (y/n): ";
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            std::string videoID = videoURL.substr(videoURL.find("v=") + 2);
            downloadYouTubeAudio(videoID);
        } else {
            std::cout << "Exiting without download.\n";
        }
    } else {
        std::cerr << "Invalid YouTube URL format. Make sure it starts with 'https://www.youtube.com/'\n";
    }

    return 0;
}
