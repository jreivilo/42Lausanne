import axios from "axios";
import React from "react";
import { Cookies } from "react-cookie";
import { redirect } from "react-router-dom";

const Login: React.FC = () => {
	return (
		<>
			<h1 className="login_rightTitle text-3xl md:text-5xl text-gray-900 absolute text-center w-full mt-[200px]">
				ft_transcendence
			</h1>
			<div className="flex h-screen w-screen">
				<div className="w-1/2 flex flex-col items-center justify-center bg-login">
					<img src={require('../assets/images/pong.png')} alt='logo pong' />
				</div>
				<div className="w-1/2 flex flex-col items-center justify-center bg-[#5685FFFF]">
					<div className="flex flex-col items-center">
						<a href={`${process.env.REACT_APP_BACKEND_URL}/auth/login`}>
							<button className="login_signin">
								<p>Sign in with</p>
								<img src={require('../assets/logos/42.svg').default} alt='42 icon' />
							</button>
						</a>
					</div>
				</div>
			</div>
		</>
	);
}

export default Login;