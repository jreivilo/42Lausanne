# Creating and Deploying Our Token

Creating an ERC-20 token on the Ethereum blockchain offers a standardized way of producing tokens that adhere to a set of defined rules. This guide simplifies the process of building and deploying your own token to the Ethereum Sepolia testnet.

## Getting Test ETH

Before deploying your token, you'll need test ETH for transaction fees on the Sepolia testnet:

1. **Install a web3 compatible wallet**: MetaMask, Phantom, or WalletConnect are recommended.
2. **Acquire test ETH**: Visit the QuickNode Multi-Chain Faucet for the Sepolia network, connect your wallet, and select "No thanks, just send me 0.05 ETH" to receive your test ETH without the need for tweeting.

*Note: A minimum Ethereum mainnet balance of 0.001 ETH is required to use the faucet.*

## Writing the Smart Contract

Using OpenZeppelin's ERC20 token standard simplifies the development process. This standard provides a secure and tested foundation for your token.

### Step 1: Create a Solidity File

- In the Ethereum Remix IDE, create a new Solidity file named `MyToken.sol`.
- Paste the following code into your new file:

    ```solidity
    // SPDX-License-Identifier: MIT
    pragma solidity ^0.8.20;

    import "@openzeppelin/contracts/token/ERC20/ERC20.sol";

    contract MyToken is ERC20 {
        constructor() ERC20("MyToken", "MT") {
            _mint(msg.sender, 1000000 * (10 ** uint256(decimals())));
        }
    }
    ```

### Key Points

- The **SPDX-License-Identifier** comment specifies the contract's license.
- The **pragma solidity** statement defines the compiler version to use.
- **import** brings in the ERC20 contract from OpenZeppelin, used as the base for your token.
- The **constructor** initializes your token with a name and symbol and mints the initial supply.

*Customize the name and symbol of your token in the constructor as needed.*

## Deployment

### Step 1: Compile the Contract

- Within Remix, click on the **Solidity compiler** button.
- Ensure the compiler version matches (`^0.8.20`) and click **Compile MyToken.sol**. A green check mark indicates successful compilation.

### Step 2: Deploy the Contract

- Navigate to **Deploy & Run Transactions**.
- Select **Injected Provider** under Environment, set your MetaMask to the Sepolia testnet, and choose **MyToken** for deployment.
- Click **Deploy**.

*Before deploying, make sure your MetaMask is configured for the Sepolia network. If not visible, enable the "Show test networks" option in MetaMask settings.*

### Step 3: Confirm the Deployment

- A MetaMask prompt will appear. Confirm the transaction to deploy your contract to the Sepolia testnet.

This guide provides a streamlined approach to creating and deploying an ERC-20 token, making it accessible even for those new to blockchain development.
