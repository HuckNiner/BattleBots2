#include <iostream>
#include <vector>
#include "raylib.h"
#include "world.h"
#include "pubsub.h"
#include "entity_view.h"
#include "botdata.h"
#include "simplebot.h"

class Controller : public Subscriber
{
private:
    World world;
    vector<EntityView*> views;

public:
    void gameLoop();
    void receiveMessage(string channel, string message, void* data);
};

int main(void)
{
    Controller controller;
    controller.gameLoop();

    return 0;
}

void Controller::gameLoop()
{
    const int screenWidth = 768;
    const int screenHeight = 576;
    int ticksThisTurn = 0;

    PubSub::subscribe("entity", this);

    InitWindow(screenWidth, screenHeight, "BBots Exercise 1");
    SetTargetFPS(60);

    // Generate the world for this exercise, returning the BotData instances for it
    vector<BotData*> botentities = world.initWorld(screenWidth, screenHeight);
    vector<BattleBot*> bots;

    // Load the BattleBot subclasses
    BattleBot* bot1 = new SimpleBot();
    bot1->data = botentities[0];
    bots.push_back(bot1);

    // Terrain assets pulled from: 
    // https://kenney-assets.itch.io/top-down-tanks-redux
    // https://kenney-assets.itch.io/pirate-pack

    int turnsOnExit = 0;

    while (!WindowShouldClose())
    {
        // Give the world a chance to progress
        world.tick();

        ticksThisTurn++;

        if (ticksThisTurn == ticksPerTurn)
        {
            ticksThisTurn = 0;

            for (BattleBot* bot : bots)
                bot->takeTurn();

            if (bot1->amOnExit())
                turnsOnExit++;
            else
                turnsOnExit = 0;

            if (turnsOnExit >= 5)
            {
                cout << "You won!" << endl;
                break;
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw the views
        for (EntityView* view : views)
            view->draw();

        EndDrawing();
    }

    CloseWindow();
}

void Controller::receiveMessage(string channel, string message, void* data)
{
    // On the "entity" channel there can be "new" and "delete" messages.

    if (channel == "entity" && message == "new")
    {
        // Create a view for the entity
        EntityView* view = new EntityView((Entity*)data);
        views.push_back(view);
    }

    if (channel == "entity" && message == "delete")
    {
        // Try to find the view for the entity that's being deleted
        for (int i = 0; i < views.size(); i++)
        {
            if (views[i]->isViewFor((Entity*)data))
            {
                // Delete this view's memory
                delete views[i];
                // Delete it from the vector
                views.erase(views.begin() + i);
                // and stop looking, since we found the right view
                break;
            }
        }
    }
}
