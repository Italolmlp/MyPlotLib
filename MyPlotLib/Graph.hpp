#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Graph : public sf::Drawable {

private:
    sf::RectangleShape _graphBox{};
    sf::RenderTexture _texture{};
    sf::Vector2f _bottomLeft{}, _topRight{};
    std::string _title{};
    int _fontSize{};
    sf::Font _font{};
public:
    //Constructors

    Graph();
    Graph(const sf::RectangleShape& graphBox, const sf::Vector2f& bottomLeft, const sf::Vector2f& topRight, const std::string& title, const int& fontSize, const sf::Font& font);
    
    //Setters

    void setGraphBox(const sf::RectangleShape& graphicBox);
    void setTitle(const std::string& title);    
    void setFontSize(const int& fontSize);
    void setFont(const sf::Font& font);
    void setBottomLeft(const sf::Vector2f& bottomLeft);
    void setTopRight(const sf::Vector2f& topRight);

    //Getters

    sf::RectangleShape getGraphBox() const;
    std::string getTitle() const;
    int getFontSize() const;
    sf::Font getFont() const;
    sf::Vector2f getBottomLeft() const;
    sf::Vector2f getTopRight() const;
    
    //Conversion Function

    sf::Vector2f convertPoint(const sf::Vector2f& point) const;

    //Basic Plot Functions

    void clear(const sf::Color& color = sf::Color::White);
    void plotPoint(const sf::Vector2f& point, const sf::Color& color = sf::Color::Black);
    void plotLine(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, const sf::Color& color = sf::Color::Black);

    //Plot Functions

    void plotData(const std::vector< sf::Vector2f >& data, const bool& drawLines = true, const bool& drawPoints = false, const sf::Color& lineColor = sf::Color::Black, const sf::Color& pointColor = sf::Color::Black);

    //Display Function
    void display();
    
    //Draw Function

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; 

};



#endif