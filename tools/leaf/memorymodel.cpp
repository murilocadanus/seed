#include "memorymodel.h"

#include <QStandardItemModel>

// http://qt-project.org/doc/qt-4.8/model-view-programming.html

AllocationItem::AllocationItem(AllocationData *data)
{
	pData = data;
}

AllocationItem::~AllocationItem()
{
	delete pData;
	pData = nullptr;
}

AllocationData *AllocationItem::getData() const
{
	return pData;
}

QVariant AllocationItem::data(int column, int role) const
{
	if (!pData)
		return QVariant();

	switch (role)
	{
		case Qt::TextColorRole:
		{
			if (pData->bFreed)
				return QVariant::fromValue(QColor(Qt::red));
		}
		break;

		case Qt::DisplayRole:
		{
			switch (column)
			{
				case 0: return pData->iTime;
				case 1: return pData->iLifetime;
				case 2: return pData->iFrame;
				case 3: return pData->iAddr;
				case 4: return pData->iSize;
				case 5: return QString("%1:%2").arg(pData->sFile).arg(pData->iLine);
				case 6: return pData->sFunction;
				case 7: return pData->sCall;
				case 8: return pData->iLine;
				case 9: return pData->bFreed;
				default: return QVariant();
			}
		}
	}

	return QVariant();
}

MemoryModel::MemoryModel(QObject *parent)
	: QAbstractTableModel(parent)
	, mMutex()
	, iTotalSize(0)
	, iMaxTotalSize(0)
	, iMaxUniqueSize(0)
	, bHexAddress(true)
{
	vHeader << tr("Time");
	vHeader << tr("Lifetime");
	vHeader << tr("Frame");
	vHeader << tr("Address");
	vHeader << tr("Size");
	vHeader << tr("File");
	vHeader << tr("Function");
	vHeader << tr("Call");
	vHeader << tr("Line");
	vHeader << tr("Free");
}

MemoryModel::~MemoryModel()
{
	qDeleteAll(vItems);
	vItems.clear();
}

int MemoryModel::columnCount(const QModelIndex &) const
{
	return vHeader.length();
}

int MemoryModel::rowCount(const QModelIndex &) const
{
	return vItems.length();
}

bool MemoryModel::insertRows(int row, int count, const QModelIndex &parent)
{
	beginInsertRows(parent, row, row + count - 1);
	endInsertRows();
	return true;
}

QVariant MemoryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return vHeader[section];

	return QVariant();
}

QVariant MemoryModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	auto col = index.column();
	auto row = index.row();

	if (col > vHeader.length())
		return QVariant();

	if (row > vItems.length())
		return QVariant();

	auto item = vItems[row];
	auto variant = item->data(col, role);

	if (col == 3 && bHexAddress && role == Qt::DisplayRole) // Addresss - FIXME: hard coded column number
	{
		auto hex = QString::number(variant.toULongLong(), 16);
		QString pad("0x0000000000000000");
		pad.chop(hex.length());
		return pad + hex;
	}

	return variant;
}

void MemoryModel::setHexadecimalAddress(bool hex)
{
	emit layoutAboutToBeChanged();
	bHexAddress = hex;
	emit layoutChanged();
}

void MemoryModel::clear()
{
	QMutexLocker lock(&mMutex);
	if (!vItems.length())
		return;

	removeRows(0, vItems.length());
	qDeleteAll(vItems);
	vItems.clear();

	iTotalSize = 0;
	iMaxTotalSize = 0;
	iMaxUniqueSize = 0;

	this->update();
}

void MemoryModel::update()
{
	emit layoutAboutToBeChanged();
	emit layoutChanged();
}

void MemoryModel::alloc(const PacketAllocationInfo *packet)
{
	auto data = new AllocationData();
	data->iFrame = packet->iFrame;
	data->iAddr = packet->iAddr;
	data->iSize = packet->iSize;
	data->sCall = QString(packet->strCall);
	data->sFile = QString(packet->strFile);
	data->sFunction = QString(packet->strFunc);
	data->iLine = packet->iLine;
	data->iTime = packet->iTime;
	data->iLifetime = packet->iLifetime;
	data->bFreed = false;

	auto item = new AllocationItem(data);

	{
		QMutexLocker lock(&mMutex);
		vItems.push_back(item);

		insertRow(vItems.length());

		iTotalSize += data->iSize;
		
		if (iTotalSize > iMaxTotalSize)
			iMaxTotalSize = iTotalSize;

		if (data->iSize > iMaxUniqueSize)
			iMaxUniqueSize = data->iSize;

		emit onTotalsChanged(iTotalSize, iMaxTotalSize, iMaxUniqueSize);
	}

	// hack: I could not get it right to get the data "refreshed" in the view when inserted on model
	// so I emit two signals to do a full layout refresh :(
	emit layoutAboutToBeChanged();
	emit layoutChanged();
}

void MemoryModel::free(const PacketFreeInfo *msg)
{
	foreach (auto obj, vItems)
	{
		auto data = obj->getData();
		if (data->iAddr == msg->iAddr && !data->bFreed)
		{
			emit layoutAboutToBeChanged(); // FIXME: problems? performance?
			data->bFreed = true;
			data->iLifetime = msg->iTime - data->iLifetime;
			emit layoutChanged();

			{
				QMutexLocker lock(&mMutex);
				iTotalSize -= data->iSize;
				emit onTotalsChanged(iTotalSize, iMaxTotalSize, iMaxUniqueSize);
			}

			return;
		}
	}
}
