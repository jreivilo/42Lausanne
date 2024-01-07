import React from "react";
import axios from "axios";
import NavBar from "../Components/Nav";

interface User {
	id: number;
	username: string;
	status: string;
	avatar: string;
}

const UsersPages: React.FC = () => {
	const [users, setUsers] = React.useState<User[]>([]);

	React.useEffect(() => {
		async function fetchData() {
			const response = await axios.get("/users/");
			setUsers(response.data);
		}

		fetchData();
	}, []);

	return (
		<>
			<NavBar />
			<h1>Users Page</h1>
			<p>Users Page content goes here.</p>
			<ul className="allUsers">
				{users.map((user) => (
					<div className="userAvatar" key={user.id}>
						<img className="userAvatar_img" src={user.avatar} alt="avatar"></img>
						<div className="userAvatar_status"><i></i></div>
						<div className="userAvatar_username">{user.username}</div>
					</div>
				))}
			</ul>
		</>
	);
}

export default UsersPages;
