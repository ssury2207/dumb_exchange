# Order Book

- Buy prices: highest first.
- Sell prices: lowest first.
- Orders at the same price: oldest first.

## Add (`A` / `F`)

Add the order to the back of the list at its price. Create the price level if needed. Save the order's location using its ID.

## Delete / Remove (`D`)

Find the order by ID and remove it completely. Remove its saved location too. If no orders remain at that price, remove the price level.

## Cancel (`X`)

Subtract the cancelled shares from the order's quantity. Keep its place in the list and its saved location.

Example: 100 shares minus 30 cancelled leaves 70.

If quantity reaches zero, remove the order, its saved location, and the price level if empty.

## Replace (`U`)

Remove the old order. Add the replacement at the back of the list at its new price, using the new ID and quantity. Keep the original buy/sell side and save the new location.

The supplied quantity is the replacement's total, not an amount to add.
