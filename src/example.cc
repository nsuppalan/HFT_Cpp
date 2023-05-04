#include "WS/client.hh"
#include "Strategies/marketMaking.hh"
#include <External/json.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <exception>

using json = nlohmann::json;

int main()
{

    try
    {
        json emptyJSON = {};
        double bid = 0;
        double ask = 0;
        double aum = 1000;
        double fees = .001;

        ftx::WSClient client;

        client.subscribe_ticker("BCH/USD");

        client.on_message([&](std::string j) {
            json tick = json::parse(j);
            json data = tick.value("data", emptyJSON);

            if (data != emptyJSON && data != NULL)
            {
                bid = data.at("bid");
                ask = data.at("ask");
            }
        });

        std::thread ws_thread(&ftx::WSClient::connect, &client);

        while (aum < 2000)
        {

            double size = aum / ask;
            double profit = MM::mmIsProfitable(fees, bid, ask, size);

            if (profit > 0)
            {
                aum += profit;
                std::cout << "Market Make Possible! Profit: " + std::to_string(profit) + "\n";
            }
            else
            {
                std::cout << "AUM: " + std::to_string(aum) + "\n";
            }
        }

        ws_thread.detach();
        std::cout << "Final AUM: " + std::to_string(aum) + "\n";
    }
    catch (...)
    {
        std::cout << "Oops! Exiting the Program";
    }

    std::cout << "Goodbye!\n";
    return 0;
}