#include "Application.h"
#include "imgui/imgui.h"
#include "classes/TicTacToe.h"
#include "classes/Logger.h"

namespace ClassGame {
        //
        // our global variables
        //
        TicTacToe *game = nullptr;
        Logger& log = Logger::GetInstance();
        bool gameOver = false;
        int gameWinner = -1;

        //
        // game starting point
        // this is called by the main render loop in main.cpp
        //
        void GameStartUp() 
        {
            log.LogGameEvent("Application Started");
            game = new TicTacToe();
            game->setUpBoard();
            log.LogGameEvent("Game Started");
        }

        //
        // game render loop
        // this is called by the main render loop in main.cpp
        //
        void RenderGame() 
        {
                ImGui::DockSpaceOverViewport();
                log.Draw();
                //ImGui::ShowDemoWindow();

                if (!game) return;
                if (!game->getCurrentPlayer()) return;
                
                ImGui::Begin("Settings");
                ImGui::Text("Current Player Number: %d", game->getCurrentPlayer()->playerNumber());
                ImGui::Text("Current Board State: %s", game->stateString().c_str());

                if (gameOver) {
                    ImGui::Text("Game Over!");
                    ImGui::Text("Winner: %d", gameWinner);
                    bool Reset = ImGui::Button("Reset Game"); ImGui::SameLine();
                    if (Reset) {
                        game->stopGame();
                        game->setUpBoard();
                        gameOver = false;
                        gameWinner = -1;
                    }
                    bool PlayAI = ImGui::Button("Play with AI");
                    if (PlayAI) {
                        game->stopGame();
                        game->setUpBoard();
                        gameOver = false;
                        gameWinner = -1;
                        game->setAIPlayer(1);
                    }
                }
                ImGui::End();

                ImGui::Begin("GameWindow");
                game->drawFrame();
                ImGui::End();
        }

        //
        // end turn is called by the game code at the end of each turn
        // this is where we check for a winner
        //
        void EndOfTurn() 
        {
            Player *winner = game->checkForWinner();
            if (winner)
            {
                gameOver = true;
                gameWinner = winner->playerNumber();
            }
            if (game->checkForDraw()) {
                gameOver = true;
                gameWinner = -1;
            }
        }
}
