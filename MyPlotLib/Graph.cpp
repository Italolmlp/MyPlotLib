#include "Graph.hpp"
    
//Setters Implementations

void Graph::setGraphBox(const sf::RectangleShape& graphBox) {
    _graphBox = graphBox;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    _texture.create(graphBox.getGlobalBounds().width,graphBox.getGlobalBounds().height, settings);
}            

void Graph::setTitle(const std::string& title) {
    _title = title;
}

void Graph::setFontSize(const int& fontSize) {
    _fontSize = fontSize;
}

void Graph::setFont(const sf::Font& font) {
    _font = font;
}

void Graph::setBottomLeft(const sf::Vector2f& bottomLeft) {
    _bottomLeft = bottomLeft;
}

void Graph::setTopRight(const sf::Vector2f& topRight) {
    _topRight = topRight;
}

//Getters Implementations

sf::RectangleShape Graph::getGraphBox() const {
    return _graphBox;
}

std::string Graph::getTitle() const {
    return _title;
}

int Graph::getFontSize() const {
    return _fontSize;
}

sf::Font Graph::getFont() const {
    return _font;
}

sf::Vector2f Graph::getBottomLeft() const {
    return _bottomLeft;
}

sf::Vector2f Graph::getTopRight() const {
    return _topRight;
}

sf::Texture Graph::getTexture() const {
    return _texture.getTexture();
}

//Constructor Implementation

Graph::Graph(const sf::RectangleShape& graphBox, const sf::Vector2f& bottomLeft, const sf::Vector2f& topRight, const std::string& title, const int& fontSize, const sf::Font& font) {
    setGraphBox(graphBox);
    setTitle(title);
    setFontSize(fontSize);
    setFont(font);
    setBottomLeft(bottomLeft);
    setTopRight(topRight);
}

//Conversion Function

sf::Vector2f Graph::convertPoint(const sf::Vector2f& point) const {

    sf::Vector2f realPoint{};
    realPoint.x = (point.x - _bottomLeft.x)*((_graphBox.getGlobalBounds().width)/(_topRight.x-_bottomLeft.x));
    realPoint.y = (_topRight.y + _bottomLeft.y - point.y)*((_graphBox.getGlobalBounds().height)/(_topRight.y-_bottomLeft.y));
    return realPoint;

}

//Basic Plot Functions Implementations
void Graph::clear(const sf::Color& color) {
    _texture.clear(color);
}

void Graph::plotPoint(const sf::Vector2f& point, const sf::Color& color) {
    
    sf::Vector2f realPoint = convertPoint(point);

    sf::Vertex  pointVertex[] = {sf::Vertex(realPoint,color)};
    _texture.draw(pointVertex, 1, sf::Points);

}    

void Graph::plotLine(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, const sf::Color& color) {

    sf::Vector2f realStartPoint = convertPoint(startPoint), realEndPoint = convertPoint(endPoint);
    
    sf::Vertex line[] = {
        sf::Vertex(realStartPoint, color),
        sf::Vertex(realEndPoint, color)
    };
    _texture.draw(line, 2, sf::Lines);
}

//Plot Functions Implementations

void Graph::plotData(const std::vector< sf::Vector2f >& data, const bool& drawLines, const bool& drawPoints, const sf::Color& lineColor, const sf::Color& pointColor) {

    for(int i=1;i<data.size();++i) {
        
        if(drawLines) {
            plotLine(data[i-1], data[i], lineColor);
        }

        if(drawPoints) {
            plotPoint(data[i-1],pointColor);
            if(i == data.size()-1) {
                plotPoint(data[i],pointColor);
            }
        }

    }

}

//Display Function Implementation

void Graph::display() {
    _texture.display();
}

//Draw Function Implementation

void Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::Sprite sprite;
    sprite.setTexture(_texture.getTexture());
    sprite.setPosition(sf::Vector2f(
        _graphBox.getGlobalBounds().left,
        _graphBox.getGlobalBounds().top
    ));
    target.draw(sprite);
}
