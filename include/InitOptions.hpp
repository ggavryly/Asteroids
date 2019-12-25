#pragma once
#include "main.hpp"

#define WIN_REG "-window (\\d+)x(\\d+)"
#define MAP_REG "-map (\\d+)x(\\d+)"
#define AST_REG "-num_asteroids (\\d+)"
#define AMMO_REG "-num_ammo (\\d+)"
#define AB_CHANCE_REG "-ability_probability (\\d+.\\d+)"

class InitOptions
{
private:
	
	class UnknownCommand : public std::exception
	{
		const char* what() const noexcept;
	};
	
	class CommandsOverFlow : public std::exception
	{
		const char* what() const noexcept;
	};
	
public:
	
	InitOptions(std::string const &);
	InitOptions(InitOptions const &);
	~InitOptions();
	
	uint16_t getWinWidth() const;
	
	uint16_t getWinHeight() const;
	
	uint16_t getAsteroidsNum() const;
	
	uint32_t getAmmoNum() const;
	
	uint32_t getMapWidth() const;
	
	uint32_t getMapHeight() const;
	
	float getAbilityChance() const;

private:
	
	void windowInit(std::string const & init_option, std::string const & regex);
	
	void mapInit(std::string const & init_option, std::string const & regex);
	
	void asteroidsInit(std::string const & init_option, std::string const & regex);
	
	void ammoInit(std::string const & init_option, std::string const & regex);
	
	void abilityChanceInit(std::string const & init_option, std::string const & regex);

private:
	uint16_t	_win_width;
	uint16_t	_win_height;
	uint16_t	_asteroids_num;
	uint32_t	_ammo_num;
	uint32_t	_map_width;
	uint32_t	_map_height;
	float		_ability_chance;
};

