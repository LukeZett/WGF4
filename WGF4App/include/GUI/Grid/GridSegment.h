#pragma once
#include <vector>

namespace WGF::UI
{
	enum SizeType
	{
		PIXELS,
		RELATIVE
	};

	enum ConstraintType
	{
		NONE = 0,
		MIN = 1,
	};

	class GridSegment
	{
		float m_size;
		SizeType m_sizeType;
		ConstraintType m_constrained = NONE;
		float m_minSize = 0.f;

	public:
		GridSegment(float size, SizeType sizeType) : m_size(size), m_sizeType(sizeType) {};

		GridSegment(float size, SizeType sizeType, float constraint) :
			m_size(size), m_sizeType(sizeType), m_constrained(MIN), m_minSize(constraint) {};

		inline float& Size() { return m_size; }

		inline const float& Size() const { return m_size; }

		inline const SizeType& SizeType() const { return m_sizeType; }

		inline const ConstraintType& Constrained() const { return m_constrained; }

		inline float& MinSize() { return m_minSize; }

		inline const float& MinSize() const { return m_minSize; }
	};

	class AbsoluteCoordGrid
	{
		std::vector<float> m_rowEnds;
		std::vector<float> m_columnEnds;

	public:
		AbsoluteCoordGrid() = default;

		inline std::vector<float>& RowEnds() { return m_rowEnds; }

		inline std::vector<float>& ColumnEnds() { return m_columnEnds; }
	};
}
