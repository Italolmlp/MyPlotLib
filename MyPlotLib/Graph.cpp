#include "Graph.hpp"
#include <iostream>
    
//Setters Implementations

void Graph::setGraphBox(const sf::RectangleShape& graphBox) {
    _graphBox = graphBox;
    _graphBox.setFillColor(sf::Color::White);
    _graphBox.setOutlineColor(sf::Color::Black);
    _graphBox.setOutlineThickness(2);
}            

void Graph::setPlotBox(const sf::RectangleShape& plotBox) {
    _plotBox = plotBox;
    _plotBox.setFillColor(sf::Color(0,0,0,0));
    _plotBox.setOutlineColor(sf::Color::Black);
    _plotBox.setOutlineThickness(2);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    _texture.create(plotBox.getLocalBounds().width,plotBox.getLocalBounds().height, settings);
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

void Graph::setText() {
    _text.setFont(_font);
    _text.setCharacterSize(_fontSize);
    _text.setString(_title);
    _text.setOrigin(
        _text.getLocalBounds().left + 0.5f*_text.getLocalBounds().width,
        _text.getLocalBounds().top
    );
    _text.setPosition(
        _graphBox.getGlobalBounds().left + 0.5f*_graphBox.getGlobalBounds().width,
        0.5f*(_plotBox.getGlobalBounds().top + _graphBox.getGlobalBounds().top + _plotBox.getGlobalBounds().height + _graphBox.getGlobalBounds().height)
    );
    _text.setFillColor(sf::Color::Black);
}

void Graph::setXScale(const double& x0, const double& xf, const int& N) {
    double idealScale = (xf-x0)/N;
    double convertedScale = idealScale*pow(10,-floor(log10(idealScale)));
    double realScale{};
    realScale = convertedScale < 1.5 ? 1 : convertedScale < 3.5 ? 2 : 5;
    realScale *= pow(10,floor(log10(idealScale)));
    double number = ceil(x0/realScale)*realScale;
    sf::Text aux;
    while(number <= xf) {
        if(abs(number/realScale) < 0.01) number = 0.0;
        double x = convertPoint(sf::Vector2f(number,0.f)).x;
        std::string s;
        std::stringstream out;
        out << std::fixed;
        out.precision(floor(log10(idealScale))<0 ? -floor(log10(idealScale)) : 0);
        out << number;
        s = out.str();
        aux.setString(s);
        aux.setFont(_font);
        aux.setCharacterSize(0.5*_fontSize);
        aux.setOrigin(
            aux.getLocalBounds().left + 0.5f*aux.getLocalBounds().width,
            aux.getLocalBounds().top
        );
        aux.setPosition(sf::Vector2f(
           _plotBox.getGlobalBounds().left + 2 + x,
           _plotBox.getGlobalBounds().top+_plotBox.getGlobalBounds().height + 0.1*(_graphBox.getGlobalBounds().top - _plotBox.getGlobalBounds().top + _graphBox.getGlobalBounds().height - _plotBox.getGlobalBounds().height) 
        ));
        aux.setFillColor(sf::Color::Black);
        _xScale.push_back(aux);
        number+=realScale;
    }
}

void Graph::setYScale(const double& y0, const double& yf, const int& N) {
    double idealScale = (yf-y0)/N;
    double convertedScale = idealScale*pow(10,-floor(log10(idealScale)));
    double realScale{};
    realScale = convertedScale < 1.5 ? 1 : convertedScale < 3.5 ? 2 : 5;
    realScale *= pow(10,floor(log10(idealScale)));
    double number = ceil(y0/realScale)*realScale;
    sf::Text aux;
    while(number <= yf) {
        if(abs(number/realScale)<0.01)number = 0.0;
        double y = convertPoint(sf::Vector2f(0.f,number)).y;
        std::string s;
        std::stringstream out;
        out << std::fixed;
        out.precision(floor(log10(idealScale))<0 ? -floor(log10(idealScale)) : 0);
        out << number;
        s = out.str();
        aux.setString(s);
        aux.setFont(_font);
        aux.setCharacterSize(0.5*_fontSize);
        aux.setOrigin(
            aux.getLocalBounds().left + aux.getLocalBounds().width,
            aux.getLocalBounds().top + 0.5f*aux.getLocalBounds().height
        );
        aux.setPosition(sf::Vector2f(
           _plotBox.getGlobalBounds().left - 0.1*(_plotBox.getGlobalBounds().left - _graphBox.getGlobalBounds().left),
           _plotBox.getGlobalBounds().top + y
        ));
        aux.setFillColor(sf::Color::Black);
        _xScale.push_back(aux);
        number+=realScale;
    }
}

//Getters Implementations

sf::RectangleShape Graph::getGraphBox() const {
    return _graphBox;
}

sf::RectangleShape Graph::getPlotBox() const {
    return _plotBox;
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

sf::Text Graph::getText() const {
    return _text;
}

//Constructor Implementation

Graph::Graph(const sf::RectangleShape& graphBox, const sf::RectangleShape& plotBox, const sf::Vector2f& bottomLeft, const sf::Vector2f& topRight, const std::string& title, const int& fontSize, const sf::Font& font) {
    setGraphBox(graphBox);
    setPlotBox(plotBox);
    setTitle(title);
    setFontSize(fontSize);
    setFont(font);
    setBottomLeft(bottomLeft);
    setTopRight(topRight);
    setText();
    setXScale(bottomLeft.x, topRight.x, plotBox.getLocalBounds().width/100);
    setYScale(bottomLeft.y, topRight.y, plotBox.getLocalBounds().height/100);
}

//Conversion Function

sf::Vector2f Graph::convertPoint(const sf::Vector2f& point) const {

    sf::Vector2f realPoint{};
    realPoint.x = (point.x - _bottomLeft.x)*((_plotBox.getLocalBounds().width)/(_topRight.x-_bottomLeft.x));
    realPoint.y = (_topRight.y + _bottomLeft.y - point.y)*((_plotBox.getLocalBounds().height)/(_topRight.y-_bottomLeft.y));
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

void Graph::plotFunction(const std::function<double(const double&)>& f, const sf::Color& color) {
    
    int N = _texture.getTexture().getSize().x;

    std::vector< sf::Vector2f > data{};

    double x0 = _bottomLeft.x;
    double xf = _topRight.x;
    double step = (xf - x0)/(N-1);

    for(int i=0;i<N;++i) {
        double x = x0 + i*step;
        data.push_back(sf::Vector2f(x,f(x)));
    }
    std::cout << "A\n";
    plotData(data, true, false, color);
}

//Display Function Implementation

void Graph::display() {
    _texture.display();
}

//Draw Function Implementation

void Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    
    sf::Sprite sprite;

    sprite.setTexture(_texture.getTexture());

    sprite.setOrigin(sf::Vector2f(
       sprite.getGlobalBounds().left + sprite.getGlobalBounds().width/2,
        sprite.getGlobalBounds().top + sprite.getGlobalBounds().height/2  
    ));

    sprite.setPosition(sf::Vector2f(
        _plotBox.getGlobalBounds().left + _plotBox.getGlobalBounds().width/2,
        _plotBox.getGlobalBounds().top + _plotBox.getGlobalBounds().height/2
    ));

    target.draw(_graphBox);
    target.draw(_text);
    for(sf::Text v : _xScale) {
        target.draw(v);
    }
    target.draw(_plotBox);
    target.draw(sprite);
}
