#include "GUI/Grid/Grid.h"
#include <GUI/Container.h>
#include "WGF4.h"

WGF::UI::Grid& WGF::UI::Grid::AddContainer(const glm::uvec2& colSpan, const glm::uvec2& rowSpan, const std::string& name)
{
	CalculateAbsoluteGrid(m_absGrid, WGF::ResizeEvent(WGF::Window().Width(), WGF::Window().Height()));
	m_containers.emplace_back(colSpan, rowSpan, name, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration);
	CalculateContainer(m_containers.back());
	return *this;
}

WGF::UI::Grid& WGF::UI::Grid::AddContainer(unsigned int column, unsigned int row, const std::string& name)
{
	return AddContainer(glm::uvec2(column, column), glm::uvec2(row, row), name);
}

void WGF::UI::Grid::CalculateAbsoluteGrid(AbsoluteCoordGrid& target, const ResizeEvent& e) const
{
	CalculateInGridDirection(target.RowEnds(), m_rows, (float)e.height, m_rowSums);
	CalculateInGridDirection(target.ColumnEnds(), m_columns, (float)e.width, m_columnSums);
}

void WGF::UI::Grid::OnFrame()
{
	for (auto& container : m_containers) container.Container().OnFrame();
}

void WGF::UI::Grid::OnResize(WGF::ResizeEvent& e)
{
	CalculateAbsoluteGrid(m_absGrid, e);
	for (auto& container : m_containers) CalculateContainer(container);
}

bool WGF::UI::Grid::CalculateSegmentSize(float& result, const GridSegment& segment, float totalSize, const Sums& sums) const
{
	float totalRelativeSize = totalSize - sums.absolute;
	result = segment.Size() * totalRelativeSize / sums.relative;

	if ((segment.Constrained() & ConstraintType::MIN) && segment.MinSize() > result)
	{
		result = segment.MinSize();
		return false;
	}
	return true;
}

void WGF::UI::Grid::CalculateInGridDirection(std::vector<float>& finalEnds, const std::vector<GridSegment>& segments, float totalSize, Sums sums) const
{
	finalEnds.resize(segments.size());

	std::vector<int> remainingIndices;
	std::vector<int> remainingIndicesSwap;
	remainingIndices.reserve(segments.size());
	remainingIndicesSwap.reserve(segments.size());

	std::vector<int>* currentIndices = &remainingIndices;
	std::vector<int>* nextIndices = &remainingIndicesSwap;

	for (size_t i = 0; i < segments.size(); i++)
	{
		if (segments[i].SizeType() == SizeType::PIXELS)
		{
			finalEnds[i] = segments[i].Size();
		}
		else
		{
			remainingIndices.emplace_back((int)i);
		}
	}

	bool shouldAdjust = true;
	while (!currentIndices->empty() && shouldAdjust)
	{
		shouldAdjust = false;
		nextIndices->clear();

		for (auto& index : *currentIndices)
		{
			if (CalculateSegmentSize(finalEnds[index], segments[index], totalSize, sums))
			{
				nextIndices->emplace_back(index); // this segment can be adjusted
			}
			else
			{
				sums.relative -= segments[index].Size();
				sums.absolute += finalEnds[index];
				shouldAdjust = true; // this segment is limited by its minimum size
			}
		}
		std::swap(currentIndices, nextIndices);
	}

	float acc = 0;
	for (auto& end : finalEnds)
	{
		acc += end;
		end = acc;
	}
}

void WGF::UI::Grid::CalculateSums()
{
	m_rowSums = { 0.0f, 0.0f };
	m_columnSums = { 0.0f, 0.0f };

	for (auto& row : m_rows)
	{
		switch (row.SizeType())
		{
		case SizeType::PIXELS:
			m_rowSums.absolute += row.Size();
			break;
		case SizeType::RELATIVE:
			m_rowSums.relative += row.Size();
			break;
		}
	}

	for (auto& column : m_columns)
	{
		switch (column.SizeType())
		{
		case SizeType::PIXELS:
			m_columnSums.absolute += column.Size();
			break;
		case SizeType::RELATIVE:
			m_columnSums.relative += column.Size();
			break;
		}
	}
}

void WGF::UI::Grid::CalculateContainer(PlacedContainer& container)
{
	UIvec2 position = UIvec2(0, 0);
	if (container.ColSpan().x > 0)
		position.x = m_absGrid.ColumnEnds()[container.ColSpan().x - 1];

	if (container.RowSpan().x > 0)
		position.y = m_absGrid.RowEnds()[container.RowSpan().x - 1];

	UIvec2 ends = UIvec2(m_absGrid.ColumnEnds()[container.ColSpan().y], m_absGrid.RowEnds()[container.RowSpan().y]);

	container.Container().Position() = position;
	container.Container().Size() = ends - position;
}
