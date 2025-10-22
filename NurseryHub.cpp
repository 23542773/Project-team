#include "NurseryHub.h"

NurseryHub::NurseryHub(SalesService& s, InventoryService& i, StaffService & st, Greenhouse& g) : sales(s), inv(i), staff(st), greenhouse(g) 
{
	sales.setHub(this);
	inv.setHub(this);
	staff.setHub(this);
}

void NurseryHub::onEvent(events::Plant& e) 
{
	using PT = events::PlantType;

  	switch (e.type) 
	{
    	case PT::Matured: 
		{
            //Function not implemented as of yet
      		auto sku = greenhouse.speciesOf(e.plantId);


      		if (!sku) 
			{
        		std::cerr << "Species of Plant not found \n";
        		return;
      		}
      	inv.addPlant(e.plantId, *sku);
      	break;
    }

    case PT::Wilted: 
	{
		inv.releasePlant(e.plantId);
		break;
    }

    case PT::Watered:
		break;
  }
}

void NurseryHub::onEvent(events::Order& e) 
{
	
}

void NurseryHub::onEvent(events::Stock& e) 
{

  using ST = events::StockType;

  switch (e.type) 
  {
  	case ST::Low: 
	{
        std::string speciesSku = e.plantId;   
      	int batch = 10;
      	greenhouse.receiveShipment(speciesSku, batch);
        break;
    }
    case ST::Reserved:
    case ST::Released:
    case ST::Sold:
    break;
  }
}

void NurseryHub::handleNewOrder(std::string customerId, std::vector<events::OrderLine>& lines) 
{
	std::vector<std::string> reservedIds;
    reservedIds.reserve(lines.size());
	for (const events::OrderLine& line : lines)
    {
        std::optional<std::string> maybePlantId = inv.reserveAnyAvailable(line.speciesSku);

        if (maybePlantId)
        {
            reservedIds.push_back(*maybePlantId);
        }
        else
        {
            std::cout << "No stock for SKU: " << line.speciesSku << "\n";
        }
    }

	if (reservedIds.empty())
    {
        std::cout << "Order failed — no available stock.\n";
        return;
    }

	std::vector<events::OrderLine> finalized;
    finalized.reserve(reservedIds.size());
    for (std::size_t i = 0; i < reservedIds.size(); ++i)
    {
        finalized.push_back(events::OrderLine{reservedIds[i], lines[i].speciesSku});
    }

    std::string orderId = sales.createOrder(customerId, finalized);
	
    std::string who = staff.leastLoaded();
    
    if (!who.empty())
    {
        staff.assignOrder(who, orderId);
        sales.assign(orderId, who);
    }
}

void NurseryHub::completeOrder(std::string orderId)
{
    std::optional<events::Order> maybe = sales.get(orderId);
    if (!maybe) return;

    const events::Order& o = *maybe;

    for (const events::OrderLine& line : o.lines) 
	{
        inv.markSold(line.plantId);
    }

    sales.updateStatus(orderId, events::OrderStatus::Completed);
    staff.completeOrder(orderId);
}

void NurseryHub::cancelOrder(std::string orderId)
{
    std::optional<events::Order> maybe = sales.get(orderId);
    if (!maybe) return;

    const events::Order& o = *maybe;

    for (const events::OrderLine& line : o.lines) 
	{
        inv.releasePlant(line.plantId);
    }

    sales.updateStatus(orderId, events::OrderStatus::Cancelled);
    staff.completeOrder(orderId);
}