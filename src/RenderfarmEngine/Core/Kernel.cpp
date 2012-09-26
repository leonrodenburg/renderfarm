#include "Kernel.h"

/**
 * Default constructor.
 */
RFCore::Kernel::Kernel()
{

}

/**
 * Destructor.
 */
RFCore::Kernel::~Kernel()
{

}

/**
 * Start rendering the world.
 */
void RFCore::Kernel::Run()
{
#ifdef DEBUG_BUILD
    Logger::GetLogger()->Log("Firing up Kernel...");
#endif
}