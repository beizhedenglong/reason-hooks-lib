type hoverType = {
  hovered: bool,
  onMouseEnter: ReactEvent.Mouse.t => unit,
  onMouseLeave: ReactEvent.Mouse.t => unit,
};

let useHover = () => {
  let (hovered, set) = React.useState(() => false);
  {
    hovered,
    onMouseEnter: _ => set(_ => true),
    onMouseLeave: _ => set(_ => false),
  };
};