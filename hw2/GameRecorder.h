#ifndef GAME_RECORDER_H_
#define GAME_RECORDER_H_

#include <vector>

class GameIterationRecorder
{
private:
	unsigned _id;
	std::vector<char> _pressedCharacters;

public:
	GameIterationRecorder(unsigned id);
	~GameIterationRecorder();

	unsigned getId() const;

	void recored(char pressedCharacter);

	typedef std::vector<char>::const_iterator const_iterator;
	GameIterationRecorder::const_iterator cbegin() const;
	GameIterationRecorder::const_iterator cend() const;
};

class GameRecorder
{
private:
	std::vector<GameIterationRecorder> _iterationRecords;

public:
	GameRecorder();
	~GameRecorder();

	void recored(unsigned iterationId, char pressedKey);

	typedef std::vector<GameIterationRecorder>::const_iterator const_iterator;
	GameRecorder::const_iterator cbegin() const;
	GameRecorder::const_iterator cend() const;
};

#endif /* GAME_RECORDER_H_ */
