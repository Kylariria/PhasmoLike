#pragma once

#include <SFML/System/Vector2.hpp>

class VectorsUtils
{
public:
	static sf::Vector2f GetVector(const int& _direction)
	{
		if (_direction == 0) return sf::Vector2f(0.0f, -1.0f);
		else if (_direction == 90) return sf::Vector2f(1.0f, 0.0f);
		else if (_direction == 180) return sf::Vector2f(0.0f, 1.0f);
		else if (_direction == 270) return sf::Vector2f(-1.0f, 0.0f);

		return sf::Vector2f(0.0f, 0.0f);
	}

	static sf::Vector2f RotateVector(const sf::Vector2f& _vector, const int& _direction)
	{
		if (_direction == 90) return sf::Vector2f(-_vector.y, _vector.x);
		else if (_direction == 180) return sf::Vector2f(-_vector.x, -_vector.y);
		else if (_direction == 270) return sf::Vector2f(_vector.y, -_vector.x);
		return _vector;
	}

	static sf::Vector2f RotateVectorOnlyNegate(const sf::Vector2f& _vector, const int& _direction)
	{
		if (_direction == 90) return sf::Vector2f(-_vector.x, _vector.y);
		else if (_direction == 180) return sf::Vector2f(-_vector.x, -_vector.y);
		else if (_direction == 270) return sf::Vector2f(_vector.x, -_vector.y);
		return _vector;
	}

	static sf::Vector2f SizeDirection(const sf::Vector2f& _size, const int& _direction)
	{
		const sf::Vector2f& _vector = AbsoluteVector(_size);

		if (_direction == 0) return -_vector;
		else if (_direction == 90) return Vector2f(_vector.x, -_vector.y);
		else if (_direction == 180) return _vector;
		else if (_direction == 270) return Vector2f(_vector.x, _vector.y);

		return Vector2f(0, 0);
	}

	static sf::Vector2f AbsoluteVector(const sf::Vector2f& _vector)
	{
		float _x = _vector.x < 0 ? _vector.x * -1 : _vector.x;
		float _y = _vector.y < 0 ? _vector.y * -1 : _vector.y;

		return sf::Vector2f(_x, _y);
	}

	static float Absolute(const float& _value)
	{
		return _value < 0 ? _value * -1 : _value;
	}

	static sf::Vector2f KeepHighestValue(const sf::Vector2f& _vector)
	{
		float _x = _vector.x;
		float _y = _vector.y;

		_x = Absolute(_x) < Absolute(_y) ? 0 : _x;
		_y = Absolute(_y) < Absolute(_x) ? 0 : _y;

		return sf::Vector2f(_x, _y);
	}
};