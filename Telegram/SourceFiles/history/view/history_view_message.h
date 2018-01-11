/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

class HistoryItem;

namespace HistoryView {

enum class Context : char {
	History,
	Feed,
	AdminLog
};

class Message
	: public RuntimeComposer
	, public ClickHandlerHost {
public:
	Message(not_null<HistoryItem*> data, Context context);

	not_null<HistoryItem*> data() const;

	int y() const {
		return _y;
	}
	void setY(int y) {
		_y = y;
	}

	HistoryBlock *block() {
		return _block;
	}
	const HistoryBlock *block() const {
		return _block;
	}
	void attachToBlock(not_null<HistoryBlock*> block, int index);
	void removeFromBlock();
	void setIndexInBlock(int index) {
		Expects(_block != nullptr);
		Expects(index >= 0);

		_indexInBlock = index;
	}
	int indexInBlock() const {
		Expects((_indexInBlock >= 0) == (_block != nullptr));
		Expects((_block == nullptr) || (_block->messages[_indexInBlock].get() == this));

		return _indexInBlock;
	}
	Message *previousInBlocks() const;
	Message *nextInBlocks() const;

	~Message();

private:
	const not_null<HistoryItem*> _data;
	int _y = 0;
	Context _context;

	HistoryBlock *_block = nullptr;
	int _indexInBlock = -1;

};

} // namespace HistoryView
