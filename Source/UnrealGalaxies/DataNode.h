#pragma once

template <class T>
class DataNode {
	public:
	DataNode(const T& _content,  const FVector& _position) : content(_content), position(_position) {

	}

	~DataNode() {
		delete this->content;
		delete this->position;
	}

	//DataNode(DataNode& node) : content(node.GetContent()), position(node.GetPosition()) {}

	T& GetContent() const {
		return this->content;
	}

	FVector& GetPosition() const {
		return this->position;
	}
	
	private:
		T& content;
		FVector& position;
		DataNode();
		DataNode(const DataNode& node);
};

