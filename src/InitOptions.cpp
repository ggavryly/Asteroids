#include "InitOptions.hpp"

const char* InitOptions::UnknownCommand::what() const noexcept
{
	return "UnknownCommand.";
}

const char* InitOptions::CommandsOverFlow::what() const noexcept
{
	return "Too many commands.";
}

void InitOptions::windowInit(std::string const & init_option, std::string const & regex)
{
	std::smatch		s_match;
	
	std::regex_match(init_option, s_match, std::regex(regex));
	if (s_match.empty())
	{
		_win_width = 800;
		_win_height = 600;
	}
	_win_width = std::stoi(s_match[1]);
	_win_height = std::stoi(s_match[2]);
}

void InitOptions::mapInit(std::string const & init_option, std::string const & regex)
{
	std::smatch		s_match;
	
	std::regex_match(init_option, s_match, std::regex(regex));
	if (s_match.empty())
	{
		_map_width = 1000;
		_map_height = 1000;
	}
	_map_width = std::stoi(s_match[1]);
	_map_height = std::stoi(s_match[2]);
}

void InitOptions::asteroidsInit(std::string const & init_option, std::string const & regex)
{
	std::smatch		s_match;
	
	std::regex_match(init_option, s_match, std::regex(regex));
	if (s_match.empty())
		_asteroids_num = 10;
	_asteroids_num = std::stoi(s_match[1]);
}

void InitOptions::ammoInit(std::string const & init_option, std::string const & regex)
{
	std::smatch		s_match;
	
	std::regex_match(init_option, s_match, std::regex(regex));
	if (s_match.empty())
		_ammo_num = 3;
	_ammo_num = std::stoi(s_match[1]);
}

void InitOptions::abilityChanceInit(std::string const & init_option, std::string const & regex)
{
	std::smatch		s_match;
	
	std::regex_match(init_option, s_match, std::regex(regex));
	if (s_match.empty())
		_ability_chance = 0.3;
	_ability_chance = std::stof(s_match[1]);
}

InitOptions::InitOptions(std::string const &init_options)
{
	std::smatch		s_match;
	
	if (init_options.length() > 1024)
		throw CommandsOverFlow();
	
	windowInit(init_options, WIN_REG);
	mapInit(init_options, MAP_REG);
	asteroidsInit(init_options, AST_REG);
	ammoInit(init_options, AMMO_REG);
	abilityChanceInit(init_options, AB_CHANCE_REG);
}

InitOptions::InitOptions(InitOptions const &)
{}

InitOptions::~InitOptions()
{}

uint16_t InitOptions::getWinWidth() const
{
	return _win_width;
}

uint16_t InitOptions::getWinHeight() const
{
	return _win_height;
}

uint16_t InitOptions::getAsteroidsNum() const
{
	return _asteroids_num;
}

uint32_t InitOptions::getAmmoNum() const
{
	return _ammo_num;
}

uint32_t InitOptions::getMapWidth() const
{
	return _map_width;
}

uint32_t InitOptions::getMapHeight() const
{
	return _map_height;
}

float InitOptions::getAbilityChance() const
{
	return _ability_chance;
}
