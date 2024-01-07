import React, { useState, useEffect, useRef } from 'react';
import NavBar from "../Components/Nav";
import { Tournaments } from '../types'

const TournamentHistory: React.FC = () => {
	return (
		<>
		<NavBar />
		<div>
			Tournament History
		</div>
		</>
	);
}

export default TournamentHistory;
