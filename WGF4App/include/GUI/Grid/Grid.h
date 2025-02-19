#pragma once
#include "GUI/GUIElement.h"
#include "GridSegment.h"
#include <GUI/Container.h>

namespace WGF::UI
{
	class Grid : public GUIElement
	{
		struct Sums
		{
			float absolute;
			float relative;
		};

		class PlacedContainer
		{
			glm::uvec2 m_colSpan;
			glm::uvec2 m_rowSpan;
			Container m_container;
		public:
			PlacedContainer(const glm::uvec2& colSpan, const glm::uvec2& rowSpan, const Container& container) 
				: m_colSpan(colSpan), m_rowSpan(rowSpan), m_container(container) {}
			
			template<typename... Args>
			PlacedContainer(const glm::uvec2& colSpan, const glm::uvec2& rowSpan, Args&&... args)
				: m_colSpan(colSpan), m_rowSpan(rowSpan), m_container(std::forward<Args>(args)...) {}

			inline glm::uvec2& ColSpan() { return m_colSpan; }

			inline glm::uvec2& RowSpan() { return m_rowSpan; }

			inline Container& Container() { return m_container; }
		};

		std::vector<GridSegment> m_rows;
		std::vector<GridSegment> m_columns;

		Sums m_rowSums = { 0, 0 };
		Sums m_columnSums = { 0, 0 };
		AbsoluteCoordGrid m_absGrid;
		std::vector<PlacedContainer> m_containers;

	public:
		Grid() = default;

		Grid(const std::vector<GridSegment>& rows, const std::vector<GridSegment>& columns) : m_rows(rows), m_columns(columns) {};

		Grid& AddRow(const GridSegment& row) { m_rows.push_back(row); CalculateSums(); return *this; }

		Grid& AddColumn(const GridSegment& column) { m_columns.push_back(column); CalculateSums(); return *this; }

		Grid& AddContainer(const glm::uvec2& colSpan, const glm::uvec2& rowSpan, const std::string& name);

		Grid& AddContainer(unsigned int column, unsigned int row, const std::string& name);

		inline std::vector<GridSegment>& Rows() { return m_rows; }

		inline std::vector<GridSegment>& Columns() { return m_columns; }

		void CalculateAbsoluteGrid(AbsoluteCoordGrid& target, const ResizeEvent& e) const;
	
		virtual void OnFrame() override;

		virtual void OnResize(WGF::ResizeEvent& e) override;

		virtual ~Grid() = default;

	private:
		bool CalculateSegmentSize(float& result, const GridSegment& segment, float totalSize, const Sums& sums) const;

		void CalculateInGridDirection(std::vector<float>& finalEnds, const std::vector<GridSegment>& segments, float totalSize, Sums sums) const;

		void CalculateSums();

		void CalculateContainer(PlacedContainer& container);
	};
}
